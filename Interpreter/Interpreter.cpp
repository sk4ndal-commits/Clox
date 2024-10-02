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
    std::vector<Token> tokens = Scanner.scanTokens(source);

    for (auto& token:tokens) {
        std::cout << token << std::endl;
    }
}
