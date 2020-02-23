#include "node.h"

//----------------------------------------------------------------------------------------------------
EmptyNode::EmptyNode() noexcept
{
	//Constructor body
}
//----------------------------------------------------------------------------------------------------
bool EmptyNode::Evaluate(const Date& date, const std::string& event) const noexcept
{
	return true;
}
//----------------------------------------------------------------------------------------------------
DateComparisonNode::DateComparisonNode(const Comparison& comprs, const Date& date) noexcept : cmpr(comprs), dt(date)
{
	//Constructor body
}
//----------------------------------------------------------------------------------------------------
bool DateComparisonNode::Evaluate(const Date& date, const std::string& event) const noexcept
{
	switch (cmpr)
	{
	case Comparison::Less:
		return date < dt;	
	case Comparison::LessOrEqual:
		return date <= dt;	
	case Comparison::Greater:
		return date > dt;	
	case Comparison::GreaterOrEqual:
		return date >= dt;	
	case Comparison::Equal:
		return date == dt;	
	case Comparison::NotEqual:
		return date != dt;
	default:
		return 0;
		break;
	}
}
//----------------------------------------------------------------------------------------------------
EventComparisonNode::EventComparisonNode(const Comparison& comprs, const std::string& event) : cmpr(comprs), evnt(event)
{
	//Constructor body
}
//----------------------------------------------------------------------------------------------------
bool EventComparisonNode::Evaluate(const Date& date, const std::string& event) const noexcept
{
	switch (cmpr)
	{
	case Comparison::Less:
		return event < evnt;
	case Comparison::LessOrEqual:
		return event <= evnt;
	case Comparison::Greater:
		return event > evnt;
	case Comparison::GreaterOrEqual:
		return event >= evnt;
	case Comparison::Equal:
		return event == evnt;
	case Comparison::NotEqual:
		return event != evnt;
	default:
		return 0;
		break;
	}
}
//----------------------------------------------------------------------------------------------------
LogicalOperationNode::LogicalOperationNode(const LogicalOperation& logical_operation, 
										   const std::shared_ptr<Node>& lhs, 
										   const std::shared_ptr<Node>& rhs) noexcept : lgc_op(logical_operation),
										   lhs_node(lhs), rhs_node(rhs)
{
	//Constructor body
}
//----------------------------------------------------------------------------------------------------
bool LogicalOperationNode::Evaluate(const Date& date, const std::string& event) const
{
	switch (lgc_op)
	{
	case LogicalOperation::Or:
		return lhs_node->Evaluate(date, event) || rhs_node->Evaluate(date, event);
	case LogicalOperation::And:
		return lhs_node->Evaluate(date, event) && rhs_node->Evaluate(date, event);
	default:
		return 0;
		break;
	}
}
//----------------------------------------------------------------------------------------------------