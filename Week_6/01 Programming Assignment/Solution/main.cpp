#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"

//----------------------------------------------------------------------------------------------------
void TestParseEvent(); // Тесты для функции ParseEvent
void TestParseDate(); // Тесты для функции ParseDate
void TestEmptyNode(); // Тесты для EmptyNode
void TestDateComparisonNode(); // Тесты для DateComparisonNode
void TestEventComparisonNode(); // Тесты для TestEventComparisonNode
void TestLogicalOperationNode(); // Тесты для TestLogicalOperationNode
void TestInsertionOrder(); // Тесты для db на порядок вставки
void TestAdd(); // Тесты для функции Add
void TestLast(); // Тесты для функции Last
void TestRemove(); // Тесты для функции RemoveIf
void TestFind(); // Тесты для функции FinIf
void TestDatabase(); // Тесты для всего проекта
//----------------------------------------------------------------------------------------------------
void TestAll()
{
    TestRunner tr;
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestParseDate, "TestParseDate");
    tr.RunTest(TestEmptyNode, "TestEmptyNode");
    tr.RunTest(TestDateComparisonNode, "TestDateComparisonNode");
    tr.RunTest(TestEventComparisonNode, "TestEventComparisonNode");
    tr.RunTest(TestLogicalOperationNode, "TestLogicalOperationNode");
    tr.RunTest(TestInsertionOrder, "TestInsertionOrder");
    tr.RunTest(TestAdd, "TestAdd");
    tr.RunTest(TestLast, "TestLast");
    tr.RunTest(TestRemove, "TestRemoveIf");
    tr.RunTest(TestFind, "TestFindIf");
    tr.RunTest(TestParseCondition, "TestParseCondition");
    tr.RunTest(TestDatabase, "TestDatabase");
}
//----------------------------------------------------------------------------------------------------
std::string ParseEvent(std::istream& is)
{
    std::string event;
    std::getline(is, event);
    return std::string(std::find_if(event.begin(), event.end(), [](const unsigned char& c) noexcept
    {
        return !std::isspace(c);
    }),
    event.end());
}
//----------------------------------------------------------------------------------------------------
int main() 
{
    TestAll();

    Database db;

    for (std::string line; std::getline(std::cin, line); ) 
    {
        std::istringstream is(line);

        std::string command;
        is >> command;

        if (command == "Add") 
        {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        }
        else 
        if (command == "Print") 
        {
            db.Print(std::cout);
        }
        else 
        if (command == "Del")
        {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const std::string& event) 
            {
                return condition->Evaluate(date, event);
            };
            const int count = db.RemoveIf(predicate);
            std::cout << "Removed " << count << " entries" << std::endl;
        }
        else 
        if (command == "Find") 
        {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const std::string& event)
            {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            for (const auto& entry : entries) 
            {
                std::cout << entry << std::endl;
            }
            std::cout << "Found " << entries.size() << " entries" << std::endl;
        }
        else 
        if (command == "Last") 
        {
            try 
            {
                std::cout << db.Last(ParseDate(is)) << std::endl;
            }
            catch (std::invalid_argument& err)
            {
                std::cout << "No entries" << std::endl;
            }
        }
        else 
        if (command.empty()) 
        {
            continue;
        }
        else 
        {
            throw std::logic_error("Unknown command: " + command);
        }
    }
    return 0;
}
//----------------------------------------------------------------------------------------------------
void TestParseEvent() 
{
    {
        std::istringstream is("event");
        AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
    }
    {
        std::istringstream is("   sport event ");
        AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
    }
    {
        std::istringstream is("  first event  \n  second event");
        std::vector<std::string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        AssertEqual(events, std::vector<std::string>{"first event  ", "second event"}, "Parse multiple events");
    }
}
//---------------------------------------------------------------------------------------------------- 