#include "ast.h"
#include <variant>

Program::Program(Lexer&& _l)
  : statements{}
  , l(std::move(_l))
  , curr{}
  , next{}
{
    advance_token();
    advance_token();
}

void
Program::advance_token()
{
    curr = next;
    next = l.next_token();
}

Expression
Program::read_expression()
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
        default: {
            return { ErrorExpression() };
        }
    }

    return { ErrorExpression() };
}

ParseSignals
Program::read_statement()
{
    switch (curr.type) {
        case TokenType::LET: {
            advance_token();

            if (curr.type != TokenType::IDENTIFIER ||
                next.type != TokenType::EQ)
                return ParseSignals::ILLEGAL;

            std::string identifier{ std::move(curr.literal) };
            advance_token();
            advance_token();

            Expression e = read_expression();
            if (std::holds_alternative<ErrorExpression>(e))
                return ParseSignals::ILLEGAL;

            LetStatement l{std::move(identifier), std::move(e)};
            statements.emplace_back(std::move(l));
        } break;
    }
    return ParseSignals::SUCCESS;
}
