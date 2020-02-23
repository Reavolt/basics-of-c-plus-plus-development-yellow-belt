#pragma once

#include "date.h"

#include <string>
#include <memory>
using namespace std;

struct Node {
  virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

struct EmptyNode : public Node {
  bool Evaluate(const Date& date, const string& event) const override;
};

enum class Comparison {
  Less,
  LessOrEqual,
  Equal,
  NotEqual,
  Greater,
  GreaterOrEqual,
};

class DateComparisonNode : public Node {
public:
  DateComparisonNode(Comparison comparison, const Date& value);
  bool Evaluate(const Date& date, const string& event) const override;

private:
  Comparison comparison_;
  Date value_;
};

class EventComparisonNode : public Node {
public:
  EventComparisonNode(Comparison comparison, const string& value);
  bool Evaluate(const Date& date, const string& event) const override;

private:
  Comparison comparison_;
  string value_;
};

enum class LogicalOperation {
  And,
  Or,
};

class LogicalOperationNode : public Node {
public:
  LogicalOperationNode(LogicalOperation operation, shared_ptr<Node> left, shared_ptr<Node> right);
  bool Evaluate(const Date& date, const string& event) const override;

private:
  LogicalOperation operation_;
  shared_ptr<Node> left_, right_;
};

void TestDateComparisonNode();
void TestEventComparisonNode();
void TestLogicalOperationNode();
