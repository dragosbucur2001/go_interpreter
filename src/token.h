#pragma once

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

    friend bool operator==(const Token& rhs, const Token& lhs);
};
