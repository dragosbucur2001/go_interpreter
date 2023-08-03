#include "ast.h"

#include <memory>
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
            Expression s{ SimpleExpression{ TRUE_TOKEN } };
            advance_token();

            return s;
        }
        case TokenType::FALSE: {
            Expression s{ SimpleExpression{ FALSE_TOKEN } };
            advance_token();

            return s;
        }
        case TokenType::INT:
        case TokenType::IDENTIFIER: {
            Expression s{ SimpleExpression{ std::move(curr) } };
            advance_token();

            if (curr.type == TokenType::SEMICOLON) {
                return s;
            }

            if (curr.is_binary_operator()) {
                auto operator_token = curr;
                advance_token();

                auto second_operand = read_expression();

                return { BinaryExpression{
                  operator_token.type,
                  std::make_shared<Expression>(std::move(s)),
                  std::make_shared<Expression>(std::move(second_operand)) } };
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
            if (std::holds_alternative<ErrorExpression>(e.expr))
                return ParseSignal::ILLEGAL;

            if (curr.type != TokenType::SEMICOLON)
                return ParseSignal::ILLEGAL;

            advance_token(); // consume SEMICOLON

            LetStatement l{ std::move(identifier), std::move(e) };
            statements.emplace_back(std::move(l));
        } break;
        case TokenType::RETURN: {
            advance_token();
            Expression e = read_expression();

            if (std::holds_alternative<ErrorExpression>(e.expr))
                return ParseSignal::ILLEGAL;

            if (curr.type != TokenType::SEMICOLON)
                return ParseSignal::ILLEGAL;

            advance_token(); // consume SEMICOLON

            ReturnStatement l{ std::move(e) };
            statements.emplace_back(std::move(l));
        } break;
        case TokenType::EOF_: {
            return ParseSignal::EMPTY;
        }
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
