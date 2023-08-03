#pragma once

#include <memory>
#include <ostream>
#include <string>
#include <variant>

#include "token.h"

// ===========
// EXPRESSIONS
// ===========

struct Expression;

struct SimpleExpression
{
    Token token;

    friend bool operator==(const SimpleExpression& lhs,
                           const SimpleExpression& rhs);

    friend std::ostream& operator<<(std::ostream& os,
                                    const SimpleExpression& e);
};

struct ErrorExpression
{
    friend bool operator==(const ErrorExpression& lhs,
                           const ErrorExpression& rhs);

    friend std::ostream& operator<<(std::ostream& os, const ErrorExpression& e);
};

struct AddExpression
{
    std::shared_ptr<Expression> lhs;
    std::shared_ptr<Expression> rhs;

    friend bool operator==(const AddExpression& lhs, const AddExpression& rhs);

    friend std::ostream& operator<<(std::ostream& os, const AddExpression& e);
};

struct Expression
{
    std::variant<SimpleExpression, ErrorExpression> expr;

    friend bool operator==(const Expression& lhs, const Expression& rhs);

    friend std::ostream& operator<<(std::ostream& os, const Expression& e);
};

// ==========
// STATEMENTS
// ==========

struct LetStatement
{
    std::string identifier;
    Expression expr;

    friend std::ostream& operator<<(std::ostream& os, const LetStatement& rhs);

    friend bool operator==(const LetStatement& lhs, const LetStatement& rhs);
};

struct ReturnStatement
{
    Expression expr;

    friend std::ostream& operator<<(std::ostream& os,
                                    const ReturnStatement& rhs);
};

typedef std::variant<LetStatement, ReturnStatement> Statement;

std::ostream&
operator<<(std::ostream& os, const Statement& e);
