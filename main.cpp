#include <cstdint>
#include <istream>
#include <sstream>
#include <string>
#include <memory>
#include <iostream>

#include "./src//lexer.h"

int main() {
    std::string line;
    std::istringstream iss;
    std::cout << ">> ";
    while (std::getline(std::cin, line)) {
        iss.str(std::move(line));
        iss.clear();
        auto stream = std::make_unique<std::istringstream>(std::move(iss));
        Lexer l{std::move(stream)};

        while (auto token = l.next_token()) {
            std::cout << token << ", ";
        }

        std::cout << "\n>> ";
    }
    
    return 0;
}
