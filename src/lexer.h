#pragma once

#include <istream>
#include <memory>

#include "token.h"

class Lexer
{
    std::unique_ptr<std::istream> input;

    // both methods expect the first char of the token
    // is still inside input
    Token read_word();
    Token read_number();

    // does NOT consume first the non-whitespace char
    void skip_whitespace();

  public:
    Lexer(std::unique_ptr<std::istream>&& _input);

    Token next_token();
};
