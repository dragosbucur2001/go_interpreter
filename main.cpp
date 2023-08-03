#include <cstdint>
#include <istream>
#include <sstream>
#include <string>
#include <memory>
#include <iostream>

#include "./src/lexer.h"
#include "./src/ast.h"

int main() {
    std::string line;
    std::istringstream iss;
    std::cout << ">> ";
    while (std::getline(std::cin, line)) {
        iss.str(std::move(line));
        iss.clear();
        auto stream = std::make_unique<std::istringstream>(std::move(iss));
        Lexer l{std::move(stream)};
        
        AST ast{std::move(l)};
        ParseSignal s = ast.build();
        std::cout << (int)s << '\n';
        ast.print_statements(std::cout);

        std::cout << "\n>> ";
    }
    
    return 0;
}
