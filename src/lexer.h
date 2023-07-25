#pragma once

#include <istream>
#include <memory>

#include "./token.h"

class Lexer
{
    std::unique_ptr<std::istream> input;
    std::uint32_t position;
    std::uint32_t readPosition;
    char byte;

  public:
    Lexer(std::unique_ptr<std::istream>&& _input);

    Token next_token();
};
