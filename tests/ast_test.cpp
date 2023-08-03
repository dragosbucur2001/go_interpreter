#include "../src/ast.h"
#include "../src/lexer.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

// Demonstrate some basic assertions.
TEST(AST, temp)
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

    AST ast{ std::move(l) };
}
