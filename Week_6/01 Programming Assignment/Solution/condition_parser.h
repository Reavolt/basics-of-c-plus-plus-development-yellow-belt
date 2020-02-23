#pragma once

#ifndef _CONDITION_PARSE_H_
#define _CONDITION_PARSE_H_

#include "node.h"
#include "test_runner.h"

#include <memory>
#include <iostream>

//----------------------------------------------------------------------------------------------------
std::shared_ptr<Node> ParseCondition(std::istream& is);
//----------------------------------------------------------------------------------------------------
void TestParseCondition();
//----------------------------------------------------------------------------------------------------
#endif // _CONDITION_PARSE_H_