#pragma once

#include "./lexer.h"
#include "./token.h"
#include <memory>
#include <string>
#include <variant>
#include <vector>

struct SimpleExpression
{
    Token token;
};

struct ErrorExpression
{};

typedef std::variant<SimpleExpression, ErrorExpression> Expression;

struct LetStatement
{
    std::string identifier;
    Expression expr;
};

struct ReturnStatement
{
    Expression expr;
};

typedef std::variant<LetStatement, ReturnStatement> Statements;

enum class ParseSignals
{
    SUCCESS,
    EMPTY,
    ILLEGAL,
};

class Program
{
    std::vector<Statements> statements;
    Lexer l;

    Token curr;
    Token next;

    void advance_token();

    // assumes that curr is on the first token of the expression
    // curr will be at the token right after expression
    Expression read_expression();

    // assumes that curr is on the first token of the line
    ParseSignals read_statement();

  public:
    Program(Lexer&& _l);
};
