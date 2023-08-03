#include "ast.h"

#include <variant>

AST::AST(Lexer&& _l) noexcept
  : statements{}
  , l(std::move(_l))
  , curr{}
  , next{}
{
    advance_token();
    advance_token();
}

void
AST::advance_token() noexcept
{
    curr = next;
    next = l.next_token();
}

Expression
AST::read_expression() noexcept
{
    switch (curr.type) {
        case TokenType::TRUE: {
            SimpleExpression s{ TRUE_TOKEN };
            advance_token();

            return s;
        }
        case TokenType::FALSE: {
            SimpleExpression s{ FALSE_TOKEN };
            advance_token();

            return s;
        }
        case TokenType::INT:
        case TokenType::IDENTIFIER: {
            if (next.type == TokenType::SEMICOLON) {
                SimpleExpression s{ std::move(curr) };
                advance_token();

                return s;
            }
        }
            [[fallthrough]];
        default: {
            return { ErrorExpression() };
        }
    }

    return { ErrorExpression() };
}

ParseSignal
AST::read_statement() noexcept
{
    switch (curr.type) {
        case TokenType::LET: {
            advance_token();

            if (curr.type != TokenType::IDENTIFIER ||
                next.type != TokenType::ASSIGN)
                return ParseSignal::ILLEGAL;

            std::string identifier{ std::move(curr.literal) };
            advance_token();
            advance_token();

            Expression e = read_expression();
            if (std::holds_alternative<ErrorExpression>(e))
                return ParseSignal::ILLEGAL;

            if (curr.type != TokenType::SEMICOLON)
                return ParseSignal::ILLEGAL;

            advance_token();

            LetStatement l{ std::move(identifier), std::move(e) };
            statements.emplace_back(std::move(l));
        } break;
        default: {
            return ParseSignal::ILLEGAL;
        }
    }
    return ParseSignal::SUCCESS;
}

ParseSignal
AST::build() noexcept
{
    ParseSignal s;
    for (s = read_statement(); s == ParseSignal::SUCCESS; s = read_statement())
        ;
    return s;
}
