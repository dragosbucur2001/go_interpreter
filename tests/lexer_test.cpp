#include "../src/lexer.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

// Demonstrate some basic assertions.
TEST(Lexer, char_tokens)
{
    Token tokens[] = {
        { TokenType::ASSIGN, "=" }, { TokenType::PLUS, "+" },
        { TokenType::LPAREN, "(" }, { TokenType::RPAREN, ")" },
        { TokenType::LBRACE, "{" }, { TokenType::RBRACE, "}" },
    };

    std::string s{ "" };
    for (const auto& t : tokens) {
        s.append(t.literal);
    }

    auto iss = std::make_unique<std::istringstream>(s);
    Lexer l(std::move(iss));

    for (const auto& t : tokens) {
        EXPECT_TRUE(t == l.next_token());
    }
}

TEST(Lexer, complex_tokens)
{
    std::string s{ "let five = 5;"
                   "let ten = 10;"
                   "let add = fn(x, y) {"
                   "    x + y;"
                   "};"
                   "let result = add(five, ten);" };

    auto iss = std::make_unique<std::istringstream>(s);
    Lexer l(std::move(iss));

    Token tokens[] = {
        { TokenType::LET, "let" },      { TokenType::IDENTIFIER, "five" },
        { TokenType::ASSIGN, "=" },     { TokenType::INT, "5" },
        { TokenType::SEMICOLON, ";" },

        { TokenType::LET, "let" },      { TokenType::IDENTIFIER, "ten" },
        { TokenType::ASSIGN, "=" },     { TokenType::INT, "10" },
        { TokenType::SEMICOLON, ";" },

        { TokenType::LET, "let" },      { TokenType::IDENTIFIER, "add" },
        { TokenType::ASSIGN, "=" },     { TokenType::FUNCTION, "fn" },
        { TokenType::LPAREN, "(" },     { TokenType::IDENTIFIER, "x" },
        { TokenType::COMMA, "," },      { TokenType::IDENTIFIER, "y" },
        { TokenType::RPAREN, ")" },     { TokenType::LBRACE, "{" },

        { TokenType::IDENTIFIER, "x" }, { TokenType::PLUS, "+" },
        { TokenType::IDENTIFIER, "y" }, { TokenType::SEMICOLON, ";" },

        { TokenType::RBRACE, "}" },     { TokenType::SEMICOLON, ";" },

        { TokenType::LET, "let" },      { TokenType::IDENTIFIER, "result" },
        { TokenType::ASSIGN, "=" },     { TokenType::IDENTIFIER, "add" },
        { TokenType::LPAREN, "(" },     { TokenType::IDENTIFIER, "five" },
        { TokenType::COMMA, "," },      { TokenType::IDENTIFIER, "ten" },
        { TokenType::RPAREN, ")" },     { TokenType::SEMICOLON, ";" },
    };

    for (const auto& t : tokens) {
        EXPECT_TRUE(t == l.next_token());
    }
}
