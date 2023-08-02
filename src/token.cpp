#include "token.h"

Token::operator bool() const
{
    return type != TokenType::ILLEGAL && type != TokenType::EOF_;
}

bool
operator==(const Token& rhs, const Token& lhs)
{
    return rhs.type == lhs.type && rhs.literal == lhs.literal;
}

std::ostream&
operator<<(std::ostream& os, const Token& lhs)
{
    os << "(" << (int)lhs.type << ", " << lhs.literal << ")";
    return os;
}
