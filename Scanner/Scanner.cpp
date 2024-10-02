//
// Created by sascha-roggatz on 02.10.24.
//

#include <vector>
#include <iostream>
#include "Scanner.h"

std::vector<Token> Scanner::scantTokens(const std::string_view &source) {
    int current = 0, start = 0, line = 1;
    std::vector<Token> tokens;

    auto addToken = [&](TokenType type) {
        addFullToken(tokens, type, source, start, current, line);
    };

    auto scanToken = [&]() {
        char c = advance(current, source);
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
    };


    while (current < source.length()) {

        start = current;
        scanToken();
    }

    Token eofToken;
    eofToken.type = TokenType::Eof;
    eofToken.lexeme = "";
    eofToken.literal = nullptr;
    eofToken.line = line;

    tokens.push_back(eofToken);
    return tokens;
}

char Scanner::advance(int &current, const std::string_view &source) {
    current++;
    return source[current-1];
}

void Scanner::addFullToken(
        std::vector<Token> &tokens,
        TokenType type,
        const std::string_view& source,
        int start,
        int current,
        int line) {
    Token t;
    t.type = type;
    t.lexeme = source.substr(start, current-start);
    t.literal = nullptr;
    t.line = line;

    tokens.push_back(t);
}