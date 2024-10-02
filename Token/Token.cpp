//
// Created by sascha-roggatz on 02.10.24.
//

#include <string_view>
#include <any>
#include <variant>
#include "../Enums/TokenType.cpp"

typedef struct Token {
    TokenType type;
    std::string_view lexeme;
    std::any literal;
    int line;
} Token;