#include "./lexer.h"
#include <iostream>

Lexer::Lexer(std::unique_ptr<std::istream>&& _input)
  : input(std::move(_input))
  , position(0)
  , readPosition(0)
  , byte(0)
{}

static bool
is_letter(char c)
{
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || (c == '_');
}

static bool
is_whitespace(char c)
{
    return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}

static bool
is_digit(char c)
{
    return ('0' <= c && c <= '9');
}

Token
Lexer::next_token()
{
    if (input->eof())
        return { TokenType::EOF_, "" };

    std::string s;
    char c;
    do {
        input->read(&c, 1);
    } while (is_whitespace(c));

    if (is_letter(c)) {
        while (is_letter(c)) {
            s += c;
            input->read(&c, 1);
        }
        input->putback(c);

        if (s == "let")
            return { TokenType::LET, "let" };

        if (s == "fn")
            return { TokenType::FUNCTION, "fn" };

        return { TokenType::IDENTIFIER, std::move(s) };
    }

    if (is_digit(c)) {
        while (is_digit(c)) {
            s += c;
            input->read(&c, 1);
        }
        input->putback(c);

        return { TokenType::INT, std::move(s) };
    }

    switch (c) {
        case '=':
            return { TokenType::ASSIGN, "=" };
        case '+':
            return { TokenType::PLUS, "+" };
        case '(':
            return { TokenType::LPAREN, "(" };
        case ')':
            return { TokenType::RPAREN, ")" };
        case '{':
            return { TokenType::LBRACE, "{" };
        case '}':
            return { TokenType::RBRACE, "}" };
        case ';':
            return { TokenType::SEMICOLON, ";" };
        case ',':
            return { TokenType::COMMA, "," };
        default:
            return { TokenType::ILLEGAL, "" };
    }
}
