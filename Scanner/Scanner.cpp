//
// Created by sascha-roggatz on 02.10.24.
//

#include <vector>
#include <iostream>
#include "Scanner.h"

Scanner::Scanner() : current(0), start(0), line(0) {}

Scanner::~Scanner() = default;

std::vector<Token> Scanner::scanTokens(const std::string_view &source) {
    this->code = source;

    while (!this->isAtEnd()) {

        this->start = this->current;
        this->scanToken();
    }

    tokens.emplace_back(TokenType::Eof, "", nullptr, line);
    return tokens;
}

char Scanner::advance() {
    return this->code[this->current++];
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
                while (peek() != '\n' && !isAtEnd())
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
            if (Scanner::isDigit(c)) {
                this->readNumber();
            } else {
                std::cerr << "Unexpected token " << c << std::endl;
            }
            break;
    }
}

bool Scanner::isAtEnd() {
    return this->current >= this->code.length();
}

bool Scanner::nextCharMatches(char expected) {
    if (this->isAtEnd() || this->code[this->current] != expected) return false;
    this->current++;
    return true;
}

char Scanner::peek() {
    return this->isAtEnd() ? '\0' : this->code[this->current];
}

char Scanner::peekNext() {
    return this->isAtEnd() ? '\0' : this->code[this->current + 1];
}

void Scanner::readString() {
    while (this->peek() != '"' && !this->isAtEnd()) {
        if (this->peek() == '\n') this->line++;
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

void Scanner::addToken(TokenType type, const std::any &literal) {
    int lexemeLength = this->current - this->start;
    std::string_view text = this->code.substr(this->start, lexemeLength);
    this->tokens.emplace_back(type, text, literal, line);
}

void Scanner::readNumber() {
    while (Scanner::isDigit(this->peek())) this->advance();

    if (this->peek() == '.' && Scanner::isDigit(this->peekNext())) {
        this->advance();

        while (Scanner::isDigit(this->peek())) this->advance();
    }

    std::string_view lexeme = this->code.substr(this->start, this->current - this->start);
    this->tokens.emplace_back(TokenType::Number, lexeme, nullptr, line);
}

bool Scanner::isDigit(char c) {
    return c >= '0' && c <= '9';
}
