#pragma once

#include <ostream>
#include <string>

enum class TokenType
{
    ILLEGAL,
    EOF_,

    // Identifiers + literals
    IDENTIFIER, // add, foobar, x, y, ...
    INT,        // 1343456

    // Operators
    ASSIGN,
    PLUS,
    EQ,
    NEQ,

    // Delimiters
    COMMA,
    SEMICOLON,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,

    // Keywords
    FUNCTION,
    LET
};

struct Token
{
    TokenType type;
    std::string literal;

    operator bool() const;
    friend bool operator==(const Token& rhs, const Token& lhs);
    friend std::ostream& operator<<(std::ostream& os, const Token& lhs);
};
