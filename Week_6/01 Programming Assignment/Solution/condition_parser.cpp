#include "condition_parser.h"
#include "token.h"

//----------------------------------------------------------------------------------------------------
template <class It>
std::shared_ptr<Node> ParseComparison(It& current, It end) 
{
    if (current == end) 
    {
        throw std::logic_error("Expected column name: date or event");
    }

    const Token& column = *current;
    if (column.type != TokenType::COLUMN)
    {
         throw std::logic_error("Expected column name: date or event");
    }
    ++current;

    if (current == end)
    {
        throw std::logic_error("Expected comparison operation");
    }

    const Token& op = *current;
    if (op.type != TokenType::COMPARE_OP)
    {
        throw std::logic_error("Expected comparison operation");
    }
    ++current;

    if (current == end) 
    {
        throw std::logic_error("Expected right value of comparison");
    }

    Comparison cmp;
    if (op.value == "<") 
    {
        cmp = Comparison::Less;
    } 
    else 
    if (op.value == "<=") 
    {
        cmp = Comparison::LessOrEqual;
    } 
    else 
    if (op.value == ">") 
    {
        cmp = Comparison::Greater;
    } 
    else 
    if (op.value == ">=") 
    {
        cmp = Comparison::GreaterOrEqual;
    } 
    else 
    if (op.value == "==") 
    {
        cmp = Comparison::Equal;
    } 
    else 
    if (op.value == "!=") 
    {
        cmp = Comparison::NotEqual;
    } 
    else 
    {
        throw std::logic_error("Unknown comparison token: " + op.value);
    }

    const std::string& value = current->value;
    ++current;

    if (column.value == "date")
    {
        std::istringstream is(value);
        return std::make_shared<DateComparisonNode>(cmp, ParseDate(is));
    } 
    else
    {
        return std::make_shared<EventComparisonNode>(cmp, value);
    }
}
//----------------------------------------------------------------------------------------------------
template <class It>
std::shared_ptr<Node> ParseExpression(It& current, It end, unsigned precedence)
{
    if (current == end) 
    {
        return std::shared_ptr<Node>();
    }

    std::shared_ptr<Node> left;

    if (current->type == TokenType::PAREN_LEFT)
    {
        ++current; // consume '('
        left = ParseExpression(current, end, 0u);

        if (current == end || current->type != TokenType::PAREN_RIGHT)
        {
            throw std::logic_error("Missing right paren");
        }
        ++current; // consume ')'
    } 
    else
    {
        left = ParseComparison(current, end);
    }

    const std::map<LogicalOperation, unsigned> precedences = 
    {
      {LogicalOperation::Or, 1}, {LogicalOperation::And, 2}
    };

    while (current != end && current->type != TokenType::PAREN_RIGHT) 
    {
        if (current->type != TokenType::LOGICAL_OP) 
        {
            throw std::logic_error("Expected logic operation");
        }

        const auto logical_operation = current->value == "AND" ? LogicalOperation::And : LogicalOperation::Or;
        const auto current_precedence = precedences.at(logical_operation);
    
        if (current_precedence <= precedence) 
        {
            break;
        }

        ++current; // consume op

        left = std::make_shared<LogicalOperationNode>(logical_operation, left, ParseExpression(current, end, current_precedence));
    }
    return left;
}
//----------------------------------------------------------------------------------------------------
std::shared_ptr<Node> ParseCondition(std::istream& is)
{
    auto tokens = Tokenize(is);
    auto current = tokens.begin();
    auto top_node = ParseExpression(current, tokens.end(), 0u);

    if (!top_node) 
    {
        top_node = std::make_shared<EmptyNode>();
    }

    if (current != tokens.end()) 
    {
        throw std::logic_error("Unexpected tokens after condition");
    }
    return top_node;
}
//----------------------------------------------------------------------------------------------------