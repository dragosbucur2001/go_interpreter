#include "expressions_statements.h"

// ===========
// EXPRESSIONS
// ===========

// SIMPLE

bool
operator==(const SimpleExpression& lhs, const SimpleExpression& rhs)
{
    return lhs.token == rhs.token;
}

std::ostream&
operator<<(std::ostream& os, const SimpleExpression& e)
{
    os << "SIMPLE: " << e.token;
    return os;
}

// ERROR

bool
operator==([[maybe_unused]] const ErrorExpression& lhs,
           [[maybe_unused]] const ErrorExpression& rhs)
{
    return true;
}

std::ostream&
operator<<(std::ostream& os, [[maybe_unused]] const ErrorExpression& e)
{
    os << "ERROR";
    return os;
}

// EXPRESSION VARIANT

std::ostream&
operator<<(std::ostream& os, const Expression& e)
{
    std::visit([&os](auto&& arg) { os << arg; }, e);
    return os;
}

// ==========
// STATEMENTS
// ==========

// LET

std::ostream&
operator<<(std::ostream& os, const LetStatement& rhs)
{
    os << "LET: "
       << "Identifier(" << rhs.identifier << ")"
       << ", Expression(" << rhs.expr << ")";
    return os;
}

bool
operator==(const LetStatement& lhs, const LetStatement& rhs)
{
    return lhs.identifier == rhs.identifier && lhs.expr == rhs.expr;
}

// RETURN

std::ostream&
operator<<(std::ostream& os, const ReturnStatement& rhs)
{
    os << "RETURN: Expression(" << rhs.expr << ")";
    return os;
}

// STATEMENT_VARIANT

std::ostream&
operator<<(std::ostream& os, const Statement& e)
{
    std::visit([&os](auto&& arg) { os << arg; }, e);
    return os;
}
