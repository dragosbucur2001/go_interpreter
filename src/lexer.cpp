#include "lexer.h"

Lexer::Lexer(std::unique_ptr<std::istream>&& _input)
  : input(std::move(_input))
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
Lexer::read_word()
{
    std::string s;
    char c;

    input->read(&c, 1);
    while (is_letter(c)) {
        s += c;
        c = input->get();
    }
    input->putback(c);

    for (const auto& token : KEYWORD_TOKENS) {
        if (s == token.literal)
            return token;
    }

    return { TokenType::IDENTIFIER, std::move(s) };
}

Token
Lexer::read_number()
{
    std::string s;
    char c;

    input->read(&c, 1);
    while (is_digit(c)) {
        s += c;
        c = input->get();
    }
    input->putback(c);

    return { TokenType::INT, std::move(s) };
}

void
Lexer::skip_whitespace()
{
    char c;
    do {
        c = input->get();
    } while (is_whitespace(c));

    input->putback(c);
}

Token
Lexer::next_token()
{
    if (input->eof() || input->bad())
        return { TokenType::EOF_, "" };

    skip_whitespace();

    char c = input->peek();

    if (is_letter(c)) {
        return read_word();
    }

    if (is_digit(c)) {
        return read_number();
    }

    // actually consume char
    c = input->get();
    switch (c) {
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
        case '<':
            return { TokenType::LT, "<" };
        case '>':
            return { TokenType::GT, ">" };
        case '=': {
            if (input->peek() == '=') {
                c = input->get();
                return { TokenType::EQ, "==" };
            } else {
                return { TokenType::ASSIGN, "=" };
            }
        }
        case '!': {
            if (input->peek() == '=') {
                c = input->get();
                return { TokenType::NEQ, "!=" };
            } else {
                return { TokenType::BANG, "!" };
            }
        }
        default:
            return { TokenType::ILLEGAL, "" };
    }
}
