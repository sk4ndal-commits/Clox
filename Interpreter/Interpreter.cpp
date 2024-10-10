//
// Created by sascha-roggatz on 26.09.24.
//
#include "Interpreter.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

void Interpreter::runFile(const std::ifstream &file) {

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string sourceString = buffer.str();
    std::string_view source = sourceString;

    run(source);
}

void Interpreter::run(const std::string_view &source) {
    Scanner scanner;
    std::vector<Token> tokens = scanner.scanTokens(source);

    for (Token &token: tokens)
        if (!token.lexeme.empty()) {
            std::cout << "Lexeme " << token.lexeme << " on line " << token.line << std::endl;
        }
}
