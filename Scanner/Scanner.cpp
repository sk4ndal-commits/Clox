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

std::vector<Token> Scanner::scanTokens(const std::string_view &source) {
    this->code = source;

    while (!this->isAtEnd()) {

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
    this->addToken(type, nullptr);
}

void Scanner::scanToken() {
    char c = advance();
    switch (c) {
        case '(':
            addToken(TokenType::LeftParen);
            break;
        case ')':
            addToken(TokenType::RightParen);
            break;
        case '{':
            addToken(TokenType::LeftBrace);
            break;
        case '}':
            addToken(TokenType::RightBrace);
            break;
        case ',':
            addToken(TokenType::Comma);
            break;
        case '.':
            addToken(TokenType::Dot);
            break;
        case '-':
            addToken(TokenType::Minus);
            break;
        case '+':
            addToken(TokenType::Plus);
            break;
        case ';':
            addToken(TokenType::Semicolon);
            break;
        case '*':
            addToken(TokenType::Star);
            break;
        case '!':
            addToken(nextCharMatches('=') ?
                     TokenType::BangEqual : TokenType::Bang);
            break;
        case '=':
            addToken(nextCharMatches('=') ?
                     TokenType::EqualEqual : TokenType::Equal);
            break;
        case '<':
            addToken(nextCharMatches('=') ?
                     TokenType::LessEqual : TokenType::Less);
            break;
        case '>':
            addToken(nextCharMatches('=') ?
                     TokenType::GreaterEqual : TokenType::Greater);
            break;
        case '/':
            if (nextCharMatches('/')) {
                while (getCurrentChar() != '\n' && !isAtEnd())
                    advance();
            } else {
                addToken(TokenType::Slash);
            }
            break;
        case ' ':
        case '\r':
        case '\t':
            break;
        case '\n':
            this->line++;
            break;
        case '"':
            this->readString();
            break;
        default:
            std::cerr << "Unexpected token " << c << std::endl;
            break;
    }
}

bool Scanner::isAtEnd() {
    return this->current >= this->code.length();
}

bool Scanner::nextCharMatches(char expected) {
    if (this->isAtEnd()) return false;
    if (this->code[this->current] != expected) return false;

    this->current++;
    return true;
}

char Scanner::getCurrentChar() {
    if (this->isAtEnd()) return '\0';
    return this->code[this->current];
}

void Scanner::readString() {
    while (this->getCurrentChar() != '"' && !this->isAtEnd()) {
        if (this->getCurrentChar() == '\n') this->line++;
        advance();
    }

    if (this->isAtEnd()) {
        std::cerr << "unterminated string" << std::endl;
    }

    advance();

    int lexemeLength = (this->current - 1) - (this->start + 1);
    std::string_view value =
            this->code.substr(this->start + 1, lexemeLength);
    addToken(TokenType::String, value);
}

void Scanner::addToken(TokenType type, std::any literal) {
    int lexemeLength = this->current - this->start;
    std::string_view text = this->code.substr(this->start, lexemeLength);

    Token t;
    t.type = type;
    t.lexeme = text;
    t.literal = literal;
    t.line = this->line;

    this->tokens.push_back(t);
}
