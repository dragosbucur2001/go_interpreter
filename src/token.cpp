#include "token.h"

bool
operator==(const Token& rhs, const Token& lhs)
{
    return rhs.type == lhs.type && rhs.literal == lhs.literal;
}
