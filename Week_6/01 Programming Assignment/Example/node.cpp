#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const string& event) const {
  return true;
}

template <typename T>
bool CompareTo(const T& lhs, const T& rhs, Comparison cmp) {
  switch (cmp) {
  case Comparison::Less:
    return lhs < rhs;
  case Comparison::LessOrEqual:
    return lhs <= rhs;
  case Comparison::Equal:
    return lhs == rhs;
  case Comparison::NotEqual:
    return lhs != rhs;
  case Comparison::Greater:
    return lhs > rhs;
  case Comparison::GreaterOrEqual:
    return lhs >= rhs;
  }
  return false; // make compiler happy
}

DateComparisonNode::DateComparisonNode(Comparison comparison, const Date& value)
  : comparison_(comparison)
  , value_(value)
{
}

bool DateComparisonNode::Evaluate(const Date& date, const string&) const {
  return CompareTo(date, value_, comparison_);
}

EventComparisonNode::EventComparisonNode(Comparison comparison, const string& value)
  : comparison_(comparison)
  , value_(value)
{
}

bool EventComparisonNode::Evaluate(const Date&, const string& event) const {
  return CompareTo(event, value_, comparison_);
}

LogicalOperationNode::LogicalOperationNode(
    LogicalOperation operation, shared_ptr<Node> left, shared_ptr<Node> right
)
  : operation_(operation)
  , left_(left)
  , right_(right)
{
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
  switch (operation_) {
  case LogicalOperation::And:
    return left_->Evaluate(date, event) && right_->Evaluate(date, event);
  case LogicalOperation::Or:
    return left_->Evaluate(date, event) || right_->Evaluate(date, event);
  }
  return false; // make compiler happy
}
