#pragma once

#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <variant>
#include <vector>

#include "expressions_statements.h"
#include "lexer.h"
#include "token.h"

enum class ParseSignal
{
    SUCCESS,
    EMPTY,
    ILLEGAL,
};

class AST
{
    std::vector<Statement> statements;
    Lexer l;

    Token curr;
    Token next;

    void advance_token() noexcept;

    // assumes that curr is on the first token of the expression
    // curr will be at the token right after expression
    Expression read_expression() noexcept;

    // assumes that curr is on the first token of the line
    ParseSignal read_statement() noexcept;

  public:
    AST(Lexer&& _l) noexcept;

    ParseSignal build() noexcept;

    void print_statements(std::ostream& os)
    {
        for (const auto& s : statements) {
            os << s;
        }
    }
};
