#pragma once

#include <array>
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
    LT,
    GT,
    BANG,

    // Delimiters
    COMMA,
    SEMICOLON,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,

    // Keywords
    FUNCTION,
    LET,
    TRUE,
    FALSE,
    IF,
    ELSE,
    RETURN,
};

struct Token
{
    TokenType type;
    std::string literal;

    operator bool() const;
    friend bool operator==(const Token& rhs, const Token& lhs);
    friend std::ostream& operator<<(std::ostream& os, const Token& lhs);
};

const Token FUNCTION_TOKEN = { TokenType::FUNCTION, "fn" };
const Token LET_TOKEN = { TokenType::FUNCTION, "let" };
const Token TRUE_TOKEN = { TokenType::TRUE, "true" };
const Token FALSE_TOKEN = { TokenType::FALSE, "false" };
const Token IF_TOKEN = { TokenType::IF, "if" };
const Token ELSE_TOKEN = { TokenType::ELSE, "else" };
const Token RETURN_TOKEN = { TokenType::RETURN, "return" };

const std::array<Token, 7> KEYWORD_TOKENS = {
    FUNCTION_TOKEN, LET_TOKEN,  TRUE_TOKEN,   FALSE_TOKEN,
    IF_TOKEN,       ELSE_TOKEN, RETURN_TOKEN,
};
