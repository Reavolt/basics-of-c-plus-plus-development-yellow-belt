#include "database.h"
#include "test_runner.h"
#include "condition_parser.h"

//----------------------------------------------------------------------------------------------------
std::string FindIf_test(const Database& db, const std::string& str)
{
	std::istringstream is(str);
	auto condition = ParseCondition(is);
	auto predicate = [condition](const Date& date, const std::string& event) 
	{
		return condition->Evaluate(date, event);
	};
	const auto entries = db.FindIf(predicate);
	std::ostringstream os;
	for (const auto& entry : entries) 
	{
		os << entry << std::endl;
	}
	os << entries.size();
	return os.str();
}
//----------------------------------------------------------------------------------------------------
int RemoveIf_test(Database& db, const std::string& str)
{
	std::istringstream is(str);
	auto condition = ParseCondition(is);
	auto predicate = [condition](const Date& date, const std::string& event) 
	{
		return condition->Evaluate(date, event);
	};
	return db.RemoveIf(predicate);
}
//----------------------------------------------------------------------------------------------------
class AlwaysFalseNode : public Node 
{
	bool Evaluate(const Date&, const std::string& event) const noexcept override
	{
		return false;
	}
};
//----------------------------------------------------------------------------------------------------
void TestParseDate()
{
	{
		std::istringstream is("0-2-31");
		AssertEqual(ParseDate(is), Date(0,2,31), "Parse Date 0-2-31");
	}	
	{
		std::istringstream is("2017-11-07");
		AssertEqual(ParseDate(is), Date(2017,11,07), "Parse Date 2017-11-07");
	}
	{
		try
		{
			std::istringstream is("--11-07");
			ParseDate(is);
		}
		catch (const std::logic_error & err)
		{
			AssertEqual(std::string(err.what()), "Wrong date format: --11-07", "Parse Date --11-07");
		}
	}	
	{
		try
		{
			std::istringstream is("1900---07");
			ParseDate(is);
		}
		catch (const std::logic_error & err)
		{
			AssertEqual(std::string(err.what()), "Wrong date format: 1900---07", "Parse Date 1900---07");
		}
	}
	{
		try
		{
			std::istringstream is("1900-10--");
			ParseDate(is);
		}
		catch (const std::logic_error & err)
		{
			AssertEqual(std::string(err.what()), "Wrong date format: 1900-10--", "Parse Date 1900-10--");
		}
	}
	{
		try
		{
			std::istringstream is("1900-13-1");
			ParseDate(is);
		}
		catch (const std::logic_error & err)
		{
			AssertEqual(std::string(err.what()), "Month value is invalid: 13", "Month value is invalid");
		}
	}
	{
		try
		{
			std::istringstream is("1900-12-35");
			ParseDate(is);
		}
		catch (const std::logic_error & err)
		{
			AssertEqual(std::string(err.what()), "Day value is invalid: 35", "Day value is invalid");
		}
	}
}
//----------------------------------------------------------------------------------------------------
void TestEmptyNode() 
{
	{
		EmptyNode en;
		Assert(en.Evaluate(Date{ 0, 1, 1 }, "abc"), "EmptyNode 1");
		Assert(en.Evaluate(Date{ 2017, 11, 18 }, "abc"), "EmptyNode 2");
		Assert(en.Evaluate(Date{ 9999, 12, 31 }, "abc"), "EmptyNode 3");
	}
}
//----------------------------------------------------------------------------------------------------
void TestDateComparisonNode() 
{
	{
		DateComparisonNode dcn(Comparison::Equal, { 2017, 11, 18 });
		Assert(dcn.Evaluate(Date{ 2017, 11, 18 }, ""), "DateComparison 1");
		Assert(!dcn.Evaluate(Date{ 2017, 11, 19 }, ""), "DateComparison 2");
	}
	{
		DateComparisonNode dcn(Comparison::NotEqual, { 2017, 11, 18 });
		Assert(dcn.Evaluate(Date{ 2017, 11, 19 }, ""), "DateComparison 3");
		Assert(!dcn.Evaluate(Date{ 2017, 11, 18 }, ""), "DateComparison 4");
	}
	{
		DateComparisonNode dcn(Comparison::Less, { 2017, 11, 18 });
		Assert(dcn.Evaluate(Date{ 2017, 11, 17 }, ""), "DateComparison 5");
		Assert(!dcn.Evaluate(Date{ 2017, 11, 18 }, ""), "DateComparison 6");
		Assert(!dcn.Evaluate(Date{ 2017, 11, 19 }, ""), "DateComparison 7");
	}
	{
		DateComparisonNode dcn(Comparison::Greater, { 2017, 11, 18 });
		Assert(dcn.Evaluate(Date{ 2017, 11, 19 }, ""), "DateComparison 8");
		Assert(!dcn.Evaluate(Date{ 2017, 11, 18 }, ""), "DateComparison 9");
		Assert(!dcn.Evaluate(Date{ 2017, 11, 17 }, ""), "DateComparison 10");
	}
	{
		DateComparisonNode dcn(Comparison::LessOrEqual, { 2017, 11, 18 });
		Assert(dcn.Evaluate(Date{ 2017, 11, 17 }, ""), "DateComparison 11");
		Assert(dcn.Evaluate(Date{ 2017, 11, 18 }, ""), "DateComparison 12");
		Assert(!dcn.Evaluate(Date{ 2017, 11, 19 }, ""), "DateComparison 13");
	}
	{
		DateComparisonNode dcn(Comparison::GreaterOrEqual, { 2017, 11, 18 });
		Assert(dcn.Evaluate(Date{ 2017, 11, 19 }, ""), "DateComparison 14");
		Assert(dcn.Evaluate(Date{ 2017, 11, 18 }, ""), "DateComparison 15");
		Assert(!dcn.Evaluate(Date{ 2017, 11, 17 }, ""), "DateComparison 16");
	}
}
//----------------------------------------------------------------------------------------------------
void TestEventComparisonNode() 
{
	{
		EventComparisonNode ecn(Comparison::Equal, "abc");
		Assert(ecn.Evaluate(Date{ 0, 1, 1 }, "abc"), "EventComparison 1");
		Assert(!ecn.Evaluate(Date{ 0, 1, 1 }, "cbe"), "EventComparison 2");
	}
	{
		EventComparisonNode ecn(Comparison::NotEqual, "abc");
		Assert(ecn.Evaluate(Date{ 0, 1, 1 }, "cde"), "EventComparison 3");
		Assert(!ecn.Evaluate(Date{ 0, 1, 1 }, "abc"), "EventComparison 4");
	}
	{
		EventComparisonNode ecn(Comparison::Less, "abc");
		Assert(ecn.Evaluate(Date{ 0, 1, 1 }, "abb"), "EventComparison 5");
		Assert(!ecn.Evaluate(Date{ 0, 1, 1 }, "abc"), "EventComparison 6");
		Assert(!ecn.Evaluate(Date{ 0, 1, 1 }, "abd"), "EventComparison 7");
	}
	{
		EventComparisonNode ecn(Comparison::Greater, "abc");
		Assert(ecn.Evaluate(Date{ 0, 1, 1 }, "abd"), "EventComparison 8");
		Assert(!ecn.Evaluate(Date{ 0, 1, 1 }, "abc"), "EventComparison 9");
		Assert(!ecn.Evaluate(Date{ 0, 1, 1 }, "abb"), "EventComparison 10");
	}
	{
		EventComparisonNode ecn(Comparison::LessOrEqual, "abc");
		Assert(ecn.Evaluate(Date{ 0, 1, 1 }, "abb"), "EventComparison 11");
		Assert(ecn.Evaluate(Date{ 0, 1, 1 }, "abc"), "EventComparison 12");
		Assert(!ecn.Evaluate(Date{ 0, 1, 1 }, "abd"), "EventComparison 13");
	}
	{
		EventComparisonNode ecn(Comparison::GreaterOrEqual, "abc");
		Assert(ecn.Evaluate(Date{ 0, 1, 1 }, "abd"), "EventComparison 14");
		Assert(ecn.Evaluate(Date{ 0, 1, 1 }, "abc"), "EventComparison 15");
		Assert(!ecn.Evaluate(Date{ 0, 1, 1 }, "abb"), "EventComparison 16");
	}
}
//----------------------------------------------------------------------------------------------------
void TestLogicalOperationNode() 
{
	{
		LogicalOperationNode lon(LogicalOperation::And, std::make_shared<EmptyNode>(), std::make_shared<EmptyNode>());
		Assert(lon.Evaluate(Date{ 0, 1, 1 }, "abc"), "LogicalOperationNode 1");
	}
	{
		LogicalOperationNode lon(LogicalOperation::And, std::make_shared<AlwaysFalseNode>(), std::make_shared<EmptyNode>());
		Assert(!lon.Evaluate(Date{ 0, 1, 1 }, "abc"), "LogicalOperationNode 2");
	}
	{
		LogicalOperationNode lon(LogicalOperation::And, std::make_shared<EmptyNode>(), std::make_shared<AlwaysFalseNode>());
		Assert(!lon.Evaluate(Date{ 0, 1, 1 }, "abc"), "LogicalOperationNode 3");
	}
	{
		LogicalOperationNode lon(LogicalOperation::And, std::make_shared<AlwaysFalseNode>(), std::make_shared<AlwaysFalseNode>());
		Assert(!lon.Evaluate(Date{ 0, 1, 1 }, "abc"), "LogicalOperationNode 4");
	}
	{
		LogicalOperationNode lon(LogicalOperation::Or, std::make_shared<EmptyNode>(), std::make_shared<EmptyNode>());
		Assert(lon.Evaluate(Date{ 0, 1, 1 }, "abc"), "LogicalOperationNode 5");
	}
	{
		LogicalOperationNode lon(LogicalOperation::Or, std::make_shared<AlwaysFalseNode>(), std::make_shared<EmptyNode>());
		Assert(lon.Evaluate(Date{ 0, 1, 1 }, "abc"), "LogicalOperationNode 6");
	}
	{
		LogicalOperationNode lon(LogicalOperation::Or, std::make_shared<EmptyNode>(), std::make_shared<AlwaysFalseNode>());
		Assert(lon.Evaluate(Date{ 0, 1, 1 }, "abc"), "LogicalOperationNode 7");
	}
	{
		LogicalOperationNode lon(LogicalOperation::Or, std::make_shared<AlwaysFalseNode>(), std::make_shared<AlwaysFalseNode>());
		Assert(!lon.Evaluate(Date{ 0, 1, 1 }, "abc"), "LogicalOperationNode 8");
	}
}
//----------------------------------------------------------------------------------------------------
void TestAdd()
{
	{
		Database db;
		db.Add({ 2017, 1, 1 }, "new year");
		db.Add({ 2017, 1, 7 }, "xmas");
		std::ostringstream out;
		db.Print(out);
		AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n", out.str(), "straight ordering");
	}
	{
		Database db;
		db.Add({ 2017, 1, 1 }, "new year");
		db.Add({ 2017, 1, 1 }, "holiday");
		std::ostringstream out;
		db.Print(out);
		AssertEqual("2017-01-01 new year\n2017-01-01 holiday\n", out.str(), "several in one day");
	}
	{
		Database db;
		db.Add({ 2017, 1, 7 }, "xmas");
		db.Add({ 2017, 1, 1 }, "new year");
		std::ostringstream out;
		db.Print(out);
		AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n", out.str(), "reverse ordering");
	}
	{
		Database db;
		db.Add({ 2017, 1, 1 }, "new year");
		db.Add({ 2017, 1, 1 }, "new year");
		db.Add({ 2017, 1, 1 }, "xmas");
		db.Add({ 2017, 1, 1 }, "new year");
		std::ostringstream out;
		db.Print(out);
		AssertEqual("2017-01-01 new year\n2017-01-01 xmas\n", out.str(), "uniq adding");
	}
	{
		Database db;
		db.Add({ 2017, 1, 1 }, "new year");
		db.Add({ 2017, 1, 1 }, "new year");
		db.Add({ 2017, 1, 1 }, "xmas");
		db.Add({ 2017, 1, 1 }, "holiday");
		db.Add({ 2017, 1, 1 }, "holiday");
		std::ostringstream out;
		db.Print(out);
		AssertEqual("2017-01-01 new year\n2017-01-01 xmas\n2017-01-01 holiday\n", out.str(), "several uniq adding");
	}
}
//----------------------------------------------------------------------------------------------------
void TestRemove() 
{
	{
		Database db;
		db.Add({ 2017, 1, 1 }, "new year");
		db.Add({ 2017, 1, 7 }, "xmas");
		db.Add({ 2017, 1, 7 }, "xmas2");
		db.Add({ 2017, 1, 7 }, "xmas3");
		db.Add({ 2017, 1, 2 }, "xmas4");
		AssertEqual(0, RemoveIf_test(db, R"(event == "nothing")"), "Remove nothing");
		AssertEqual(1, RemoveIf_test(db, R"(event == "xmas2")"), "Remove xmas2");
		AssertEqual(1, RemoveIf_test(db, R"(date == "2017-01-01")"), "Remove by date1");
		AssertEqual(2, RemoveIf_test(db, R"(date == "2017-01-07")"), "Remove by date2");
		std::ostringstream out;
		db.Print(out);
		AssertEqual("2017-01-02 xmas4\n", out.str(), "Remove by date, left");
	}
	{
		Database db;
		db.Add({ 2017, 1, 1 }, "new year");
		db.Add({ 2017, 1, 7 }, "xmas");
		AssertEqual(1, RemoveIf_test(db, R"(event == "xmas")"), "Remove by event");
		std::ostringstream out;
		db.Print(out);
		AssertEqual("2017-01-01 new year\n", out.str(), "Remove by event, left");
	}
	{
		Database db;
		db.Add({ 2017, 1, 1 }, "new year");
		db.Add({ 2017, 1, 7 }, "xmas");
		db.Add({ 2017, 1, 7 }, "new year");
		AssertEqual(2, RemoveIf_test(db, R"(event == "new year")"), "Multiple remove by event");
		std::ostringstream out;
		db.Print(out);
		AssertEqual("2017-01-07 xmas\n", out.str(), "Multiple remove by event, left");
	}
}
//----------------------------------------------------------------------------------------------------
void TestFind() 
{
	{
		Database db;
		db.Add({ 2017, 1, 1 }, "new year");
		db.Add({ 2017, 1, 7 }, "xmas");
		AssertEqual("2017-01-01 new year\n1", FindIf_test(db, "date == 2017-01-01"), "simple find by date");
		AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n2", FindIf_test(db, "date < 2017-01-31"), "multiple find by date");
		AssertEqual("2017-01-01 new year\n1", FindIf_test(db, R"(event != "xmas")"), "multiple find by holiday");
	}
	{
		Database db;
		db.Add({ 2017, 1, 1 }, "new year");
		db.Add({ 2017, 1, 1 }, "new year2");
		db.Add({ 2017, 1, 7 }, "xmas");
		AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n2", FindIf_test(db, R"(date == 2017-01-07 OR event == "new year")"),
			"complex find or");
		AssertEqual("2017-01-01 new year\n1", FindIf_test(db, R"(date == 2017-01-01 AND event == "new year")"),
			"complex find and");
		AssertEqual("0", FindIf_test(db, R"(date == 2017-01-09 AND event == "new year")"),
			"complex find and, nothing");
	}
	{
		Database db;
		db.Add({ 2017, 1, 1 }, "new year");
		db.Add({ 2017, 1, 1 }, "Holiday");
		db.Add({ 2017, 1, 7 }, "xmas");
		AssertEqual("2017-01-07 xmas\n1", FindIf_test(db, "date == 2017-01-07"), "single find by date");
		AssertEqual("2017-01-01 new year\n2017-01-01 Holiday\n2017-01-07 xmas\n3", FindIf_test(db, "date < 2017-01-31"), "multiple find by date");
		AssertEqual("2017-01-01 new year\n2017-01-01 Holiday\n2", FindIf_test(db, R"(event != "xmas")"), "multiple find by event != xmas ");
		AssertEqual("2017-01-01 Holiday\n2017-01-07 xmas\n2", FindIf_test(db, R"(event != "new year")"), "multiple find by event != new year");
	}
}
//----------------------------------------------------------------------------------------------------
void TestLast()
{
	Database db;
	db.Add({ 2017, 1, 1 }, "new year");
	db.Add({ 2017, 1, 7 }, "xmas");
	{
		try 
		{
			db.Last({ 2016, 12, 31 });
			Assert(false, "last, found no entries");
		}
		catch (...) 
		{
			Assert(true, "last, found no entries");

		}
	}
	{
		std::ostringstream os;
		os << db.Last({ 2017, 1, 2 });
		AssertEqual("2017-01-01 new year", os.str(), "greater than date");
	}
	{
		std::ostringstream os;
		os << db.Last({ 2017, 1, 1 });
		AssertEqual("2017-01-01 new year", os.str(), "eq to date");
	}
	{
		std::ostringstream os;
		os << db.Last({ 2017, 1, 10 });
		AssertEqual("2017-01-07 xmas", os.str(), "greater than max date");
	}
	{
		std::ostringstream os;
		os << db.Last({ 2017, 1, 6 });
		AssertEqual("2017-01-01 new year", os.str(), "greater than before max");
	}
}
//----------------------------------------------------------------------------------------------------
void TestInsertionOrder()
{
	{
		Database db;
		db.Add({ 2017, 1, 1 }, "new year");
		db.Add({ 2017, 1, 7 }, "xmas");
		db.Add({ 2017, 1, 7 }, "party");
		db.Add({ 2017, 1, 7 }, "pie");
		std::ostringstream out;
		db.Print(out);
		AssertEqual("2017-01-01 new year\n2017-01-07 xmas\n2017-01-07 party\n2017-01-07 pie\n", out.str(), "Remove by date, left");
	}

}
//----------------------------------------------------------------------------------------------------
void TestDatabase() 
{
	std::istringstream empty_is("");
	auto const empty_condition = ParseCondition(empty_is);
	auto empty_predicate = [empty_condition](const Date& date, const std::string& event)
	{
		return empty_condition->Evaluate(date, event);
	};

	//Add 2 - Del 1 - Add deleted again
	{
		Database db;
		Date const d(2019, 1, 1);
		db.Add(d, "e1");
		db.Add(d, "e2");
		std::istringstream is(R"(event == "e1")");
		auto const condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const std::string& event) 
		{
			return condition->Evaluate(date, event);
		};
		AssertEqual(db.RemoveIf(predicate), 1, "Db Add2-Del-Add 1");
		db.Add(d, "e1");
		AssertEqual(db.FindIf(empty_predicate).size(), 2, "Db Add2-Del-Add 2");
	}
	{
		Database db;
		Date const d(2019, 1, 1);
		db.Add(d, "e1");
		db.Add(d, "e1");
		std::istringstream is("date == 2019-01-01");
		auto const condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const std::string& event)
		{
			return condition->Evaluate(date, event);
		};
		AssertEqual(db.FindIf(predicate).size(), 1, "db Add Duplicates 1");
	}

	// Last
	{
		Database db;
		Date const d(2019, 1, 1);
		Date const d1(2019, 1, 2);
		Date const d2(2018, 12, 22);
		db.Add(d1, "e1");
		db.Add(d2, "e2");
		AssertEqual(db.Last(d), ((Date(2018, 12, 22).DateToStr()) + " e2"), "db Last 1");
		Date const d3(2018, 12, 24);
		db.Add(d3, "e3");
		AssertEqual(db.Last(d), ((Date(2018, 12, 24).DateToStr()) + " e3"), "db Last 2");

		// Get last event for date before first event 
		try 
		{
			Date const d4(2017, 2, 2);
			db.Last(d4);
			Assert(false, "db Last 3");
		}
		catch (const std::invalid_argument& e) 
		{
			//std::cout << e.what() << std::endl; PASS
		}

		// Delete event and get last
		std::istringstream is("date == 2018-12-24");
		auto const condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const std::string& event) 
		{
			return condition->Evaluate(date, event);
		};
		db.RemoveIf(predicate);
		AssertEqual(db.Last(d), ((Date(2018, 12, 22).DateToStr()) + " e2"), "db Last 4");
		AssertEqual(db.Last(d1), ((Date(2019, 1, 2).DateToStr()) + " e1"), "Db Last 5");
		db.Add(d2, "e4");
		AssertEqual(db.Last(d2), ((Date(2018, 12, 22).DateToStr()) + " e4"), "db Last 6");
	}

	// Del
	{
		Database db;
		db.Add({ 2019, 1, 1 }, "e1");
		db.Add({ 2019, 1, 1 }, "e2");
		db.Add({ 2018, 1, 7 }, "e3");
		db.Add({ 2018, 1, 7 }, "e4");
		std::istringstream is("date == 2018-01-07");
		auto const condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const std::string& event)
		{
			return condition->Evaluate(date, event);
		};
		AssertEqual(db.RemoveIf(predicate), 2, "db Del 1");
	}
	{
		Database db;
		db.Add({ 2019, 1, 1 }, "e1");
		db.Add({ 2019, 1, 1 }, "e2");
		db.Add({ 2018, 1, 7 }, "e3");
		db.Add({ 2018, 1, 7 }, "e4");
		std::istringstream is("date >= 2018-01-07 AND date <= 2020-01-01");
		auto const condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const std::string& event)
		{
			return condition->Evaluate(date, event);
		};
		AssertEqual(db.RemoveIf(predicate), 4, "db Del 2");
	}
	{
		Database db;
		db.Add({ 2019, 1, 1 }, "e1");
		db.Add({ 2019, 1, 1 }, "e2");
		db.Add({ 2018, 1, 7 }, "e3");
		db.Add({ 2018, 1, 7 }, "e4");
		AssertEqual(db.RemoveIf(empty_predicate), 4, "db Del 3");
	}
	{
		Database db;
		db.Add({ 2019, 1, 1 }, "e1");
		db.Add({ 2019, 1, 1 }, "e2");
		db.Add({ 2018, 1, 7 }, "e3");
		db.Add({ 2018, 1, 7 }, "e4");
		std::istringstream is(R"(event == "e1")");
		auto const condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const std::string& event) {
			return condition->Evaluate(date, event);
		};
		AssertEqual(db.RemoveIf(predicate), 1, "db Del 4");
	}
	{
		Database db;
		db.Add({ 2019, 1, 1 }, "e1");
		db.Add({ 2019, 1, 1 }, "e2");
		db.Add({ 2018, 1, 7 }, "e3");
		db.Add({ 2018, 1, 7 }, "e4");
		std::istringstream is(R"(event == "e1" OR date == 2019-01-01)");
		auto const condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const std::string& event)
		{
			return condition->Evaluate(date, event);
		};
		AssertEqual(db.RemoveIf(predicate), 2, "db Del 5");
	}

	// Find
	{
		Database db;
		db.Add({ 2019, 1, 1 }, "e1");
		db.Add({ 2019, 1, 1 }, "e2");
		db.Add({ 2018, 1, 7 }, "e3");
		db.Add({ 2018, 1, 7 }, "e4");
		std::istringstream is("date == 2018-01-07");
		auto const condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const std::string& event)
		{
			return condition->Evaluate(date, event);
		};
		AssertEqual(db.FindIf(predicate).size(), 2, "db Find 1"); //-V807
	}
	{
		Database db;
		db.Add({ 2019, 1, 1 }, "e1");
		db.Add({ 2019, 1, 1 }, "e2");
		db.Add({ 2018, 1, 7 }, "e3");
		db.Add({ 2018, 1, 7 }, "e4");
		std::istringstream is("date >= 2018-01-07 AND date <= 2020-01-01");
		auto const condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const std::string& event) 
		{
			return condition->Evaluate(date, event);
		};
		AssertEqual(db.FindIf(predicate).size(), 4, "db Find 2");
	}
	{
		Database db;
		db.Add({ 2019, 1, 1 }, "e1");
		db.Add({ 2019, 1, 1 }, "e2");
		db.Add({ 2018, 1, 7 }, "e3");
		db.Add({ 2018, 1, 7 }, "e4");
		AssertEqual(db.FindIf(empty_predicate).size(), 4, "db Find 3");
	}
	{
		Database db;
		db.Add({ 2019, 1, 1 }, "e1");
		db.Add({ 2019, 1, 1 }, "e2");
		db.Add({ 2018, 1, 7 }, "e3");
		db.Add({ 2018, 1, 7 }, "e4");
		std::istringstream is(R"(event == "e1")");
		auto const condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const std::string& event)
		{
			return condition->Evaluate(date, event);
		};
		AssertEqual(db.FindIf(predicate).size(), 1, "db Find 4");
	}
	{
		Database db;
		db.Add({ 2019, 1, 1 }, "e1");
		db.Add({ 2019, 1, 1 }, "e2");
		db.Add({ 2018, 1, 7 }, "e3");
		db.Add({ 2018, 1, 7 }, "e4");
		std::istringstream is(R"(event == "e1" OR date == 2019-01-01)");
		auto const condition = ParseCondition(is);
		auto predicate = [condition](const Date& date, const std::string& event) {
			return condition->Evaluate(date, event);
		};
		AssertEqual(db.FindIf(predicate).size(), 2, "db Find 5");
	}

	// Add - Del - Add - Del
	{
		Database db;
		db.Add({ 2019, 1, 1 }, "e1");
		db.Add({ 2019, 1, 1 }, "e2");
		AssertEqual(db.RemoveIf(empty_predicate), 2, "db Add-Del-Add-Del 1");

		db.Add({ 2019, 1, 1 }, "e1");
		db.Add({ 2019, 1, 1 }, "e2");
		AssertEqual(db.RemoveIf(empty_predicate), 2, "db Add-Del-Add-Del 1");
	}
	{
		Database db;
		db.Add({ 2017, 1, 1 }, "first");
		db.Add({ 2017, 1, 1 }, "second");
		db.Add({ 2017, 1, 1 }, "third");
		db.Add({ 2017, 1, 1 }, "fourth");
		db.Add({ 2017, 1, 1 }, "five");
		AssertEqual(2, RemoveIf_test(db, R"(event == "second" OR event == "fourth")"), "Remove several");
		std::ostringstream os;
		db.Print(os);
		AssertEqual("2017-01-01 first\n2017-01-01 third\n2017-01-01 five\n", os.str(), "Check print after remove several- 3");
	}
}
//----------------------------------------------------------------------------------------------------