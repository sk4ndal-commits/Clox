//
// Created by sascha-roggatz on 02.10.24.
//

#include <vector>
#include <iostream>
#include "Scanner.h"

Scanner::Scanner() {
    this->current = 0;
    this->start = 0;
    this->line = 1;
}

Scanner::~Scanner() = default;

std::vector<Token> Scanner::scantTokens(const std::string_view &source) {
    this->code = source;

    while (this->current < this->code.length()) {

        this->start = this->current;
        this->scanToken();
    }

    Token eofToken;
    eofToken.type = TokenType::Eof;
    eofToken.lexeme = "";
    eofToken.literal = nullptr;
    eofToken.line = line;

    tokens.push_back(eofToken);
    return tokens;
}

char Scanner::advance() {
    this->current++;
    return this->code[this->current - 1];
}

void Scanner::addToken(TokenType type) {
    Token t;
    t.type = type;
    t.lexeme = this->code.substr(this->start, this->current - this->start);
    t.literal = nullptr;
    t.line = this->line;

    this->tokens.push_back(t);
}

void Scanner::scanToken() {
    char c = advance();
    switch (c) {
        case '(':{
            addToken(TokenType::LeftParen);
            break;
        }
        case ')': {
            addToken(TokenType::RightParen);
            break;
        }
        case '{': {
            addToken(TokenType::LeftBrace);
            break;
        }
        case '}': {
            addToken(TokenType::RightBrace);
            break;
        }
        case ',': {
            addToken(TokenType::Comma);
            break;
        }
        case '.': {
            addToken(TokenType::Dot);
            break;
        }
        case '-': {
            addToken(TokenType::Minus);
            break;
        }
        case '+': {
            addToken(TokenType::Plus);
            break;
        }
        case ';': {
            addToken(TokenType::Semicolon);
            break;
        }
        case '/': {
            addToken(TokenType::Slash);
            break;
        }
        case '*': {
            addToken(TokenType::Star);
            break;
        }
        default: {
            std::cerr << "Unexpected token " << c << std::endl;
            break;
        }
    }
}