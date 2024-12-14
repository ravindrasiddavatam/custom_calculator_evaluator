#include <iostream>
#include <string>
#include "calculator_lexer.h"
#include "calculator_parser.h"
#include "ref_env.h"
#include <fstream>

int main(int argc, char *argv[]) {
    CalculatorLexer lexer;
    CalculatorParser parser;
    std::string code;
    RefEnv global;
    if (argc == 2) {
        std::ifstream readstream;
        readstream.open(argv[1]);
        if (!readstream.is_open()) return 1;
        while (std::getline(readstream, code)) {
            lexer.input(code);
            ASTNode *tree = parser.parse(&lexer);
            ASTResult result = tree->eval(&global);
            delete tree;
        }
        readstream.close();
    } else {
        for (;;) {
            std::cout << "> ";
            std::getline(std::cin, code);
            if (!std::cin) break;
            lexer.input(code);
            ASTNode *tree = parser.parse(&lexer);
            ASTResult result = tree->eval(&global);
            delete tree;
            if (result.type == ASTResult::INT) {
                std::cout << result.value.i << std::endl;
            } else if (result.type == ASTResult::REAL) {
                std::cout << result.value.r << std::endl;
            }
        }
    }
    return 0;
}
