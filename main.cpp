#include <cstdint>
#include <istream>
#include <string>
#include <memory>

struct Token {
    enum class Type {
        ILLEGAL,
        EOF_,

        // Identifiers + literals
        IDENTIFIER, // add, foobar, x, y, ...
        INT, // 1343456

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
    
    Type type;
    std::string literal;
};

struct Lexer {
    std::shared_ptr<std::istream> input;
    std::uint32_t                 position;
    std::uint32_t                 readPosition;
    char                          byte;

    Lexer(std::shared_ptr<std::istream>& _input)
    : input(_input)
    , position(0)
    , readPosition(0)
    , byte(0)
    {}
};

int main() {
    return 0;
}
