#pragma once

#ifndef _NODE_H_
#define _NODE_H_

#include "date.h"

#include <map>
#include <set>

//----------------------------------------------------------------------------------------------------
enum class Comparison
{
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};
//----------------------------------------------------------------------------------------------------
enum class LogicalOperation
{
	Or,
	And
};
//----------------------------------------------------------------------------------------------------
class Node
{
public:
	virtual bool Evaluate(const Date& date, const std::string& event) const = 0;
	virtual ~Node() = default;
};
//----------------------------------------------------------------------------------------------------
class EmptyNode : public Node
{
public:
	EmptyNode() noexcept;
	bool Evaluate(const Date& date, const std::string& event) const noexcept override;
};
//----------------------------------------------------------------------------------------------------
class DateComparisonNode : public Node
{
public:
	DateComparisonNode(const Comparison& comprs, const Date& date) noexcept;
	bool Evaluate(const Date& date, const std::string& event) const noexcept override;
private:
	const Comparison cmpr;
	const Date dt;
};
//----------------------------------------------------------------------------------------------------
class EventComparisonNode : public Node
{
public:
	EventComparisonNode(const Comparison& comprs, const std::string& event);
	bool Evaluate(const Date& date, const std::string& event) const noexcept override;
private:
	const Comparison cmpr;
	const std::string evnt;
};
//----------------------------------------------------------------------------------------------------
class LogicalOperationNode : public Node
{
public:
	LogicalOperationNode(const LogicalOperation& logical_operation, 
						 const std::shared_ptr<Node>& lhs,
						 const std::shared_ptr<Node>& rhs) noexcept;
	bool Evaluate(const Date& date, const std::string& event) const override;
private:
	const LogicalOperation lgc_op;
	const std::shared_ptr<Node> lhs_node;
	const std::shared_ptr<Node> rhs_node;
};
//----------------------------------------------------------------------------------------------------
#endif // _NODE_H_