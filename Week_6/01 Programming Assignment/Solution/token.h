#pragma once

#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <sstream>
#include <vector>
#include <stdexcept>

//----------------------------------------------------------------------------------------------------
enum class TokenType 
{
    DATE,
    EVENT,
    COLUMN,
    LOGICAL_OP,
    COMPARE_OP,
    PAREN_LEFT,
    PAREN_RIGHT,
};
//----------------------------------------------------------------------------------------------------
struct Token 
{
    const std::string value;
    const TokenType type;
};
//----------------------------------------------------------------------------------------------------
std::vector<Token> Tokenize(std::istream& cl);
//----------------------------------------------------------------------------------------------------
#endif // _TOKEN_H_