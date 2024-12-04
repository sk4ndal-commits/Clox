//
// Created by sascha-roggatz on 02.10.24.
//

#include <vector>
#include <iostream>
#include <unordered_map>
#include "Scanner.h"

std::unordered_map<std::string_view, TokenType> keywords;

void Scanner::initializeKeywords()
{
    keywords["and"] = TokenType::And;
    keywords["class"] = TokenType::Class;
    keywords["else"] = TokenType::Else;
    keywords["false"] = TokenType::False;
    keywords["for"] = TokenType::For;
    keywords["fun"] = TokenType::Fun;
    keywords["if"] = TokenType::If;
    keywords["nil"] = TokenType::Nil;
    keywords["or"] = TokenType::Or;
    keywords["print"] = TokenType::Print;
    keywords["return"] = TokenType::Return;
    keywords["super"] = TokenType::Super;
    keywords["this"] = TokenType::This;
    keywords["true"] = TokenType::True;
    keywords["var"] = TokenType::Var;
    keywords["while"] = TokenType::While;
}

// Scanner constructor
Scanner::Scanner() : current(0), start(0), line(0)
{
    initializeKeywords();
}

Scanner::~Scanner() = default;

std::vector<Token>& Scanner::scanTokens(const std::string_view &source)
{
    this->code = source;

    while (!this->isAtEnd())
    {
        this->start = this->current;
        this->scanToken();
    }

    this->tokens.emplace_back(TokenType::Eof, "", nullptr, line);
    return this->tokens;
}

char Scanner::advance()
{
    return this->code[this->current++];
}

void Scanner::addToken(TokenType type)
{
    this->addToken(type, nullptr);
}

void Scanner::scanToken()
{
    char c = this->advance();
    switch (c)
    {
        case '(':
            this->addToken(TokenType::LeftParen);
            break;
        case ')':
            this->addToken(TokenType::RightParen);
            break;
        case '{':
            this->addToken(TokenType::LeftBrace);
            break;
        case '}':
            this->addToken(TokenType::RightBrace);
            break;
        case ',':
            this->addToken(TokenType::Comma);
            break;
        case '.':
            this->addToken(TokenType::Dot);
            break;
        case '-':
            this->addToken(TokenType::Minus);
            break;
        case '+':
            this->addToken(TokenType::Plus);
            break;
        case ';':
            this->addToken(TokenType::Semicolon);
            break;
        case '*':
            this->addToken(TokenType::Star);
            break;
        case '!':
            this->addToken(this->nextCharMatches('=')
                               ? TokenType::BangEqual
                               : TokenType::Bang);
            break;
        case '=':
            this->addToken(this->nextCharMatches('=')
                               ? TokenType::EqualEqual
                               : TokenType::Equal);
            break;
        case '<':
            this->addToken(this->nextCharMatches('=')
                               ? TokenType::LessEqual
                               : TokenType::Less);
            break;
        case '>':
            this->addToken(this->nextCharMatches('=')
                               ? TokenType::GreaterEqual
                               : TokenType::Greater);
            break;
        case '/':
            if (this->nextCharMatches('/'))
            {
                while (this->peek() != '\n' && !this->isAtEnd())
                    this->advance();
            } else
            {
                this->addToken(TokenType::Slash);
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
            if (Scanner::isDigit(c))
            {
                this->readNumber();
            } else if (Scanner::isAlpha(c))
            {
                this->readIdentifier();
            } else
            {
                std::cerr << "Unexpected token " << c << std::endl;
            }
            break;
    }
}

bool Scanner::isAtEnd() const
{
    return this->current >= this->code.length();
}

bool Scanner::nextCharMatches(const char expected)
{
    if (this->isAtEnd() || this->code[this->current] != expected) return false;
    this->current++;
    return true;
}

char Scanner::peek() const
{
    return this->isAtEnd() ? '\0' : this->code[this->current];
}

char Scanner::peekNext() const
{
    return this->current + 1 >= this->code.length()
               ? '\0'
               : this->code[this->current + 1];
}

void Scanner::readString()
{
    while (this->peek() != '"' && !this->isAtEnd())
    {
        if (this->peek() == '\n') this->line++;
        advance();
    }

    if (this->isAtEnd())
    {
        std::cerr << "unterminated string" << std::endl;
    }

    advance();

    const auto lexemeLength = this->current - 1 - (this->start + 1);
    const auto value = this->code.substr(this->start + 1, lexemeLength);
    this->addToken(TokenType::String, value);
}

void Scanner::addToken(TokenType type, const std::any &literal)
{
    const auto lexemeLength = this->current - this->start;
    const auto text = this->code.substr(this->start, lexemeLength);
    this->tokens.emplace_back(type, text, literal, line);
}

void Scanner::readNumber()
{
    while (isDigit(this->peek())) this->advance();

    if (this->peek() == '.' && Scanner::isDigit(this->peekNext()))
    {
        this->advance();

        while (isDigit(this->peek())) this->advance();
    }

    const auto lexeme = this->code.substr(
        this->start, this->current - this->start);
    this->tokens.emplace_back(TokenType::Number, lexeme, nullptr, line);
}

bool Scanner::isDigit(const char c)
{
    return c >= '0' && c <= '9';
}

bool Scanner::isAlpha(const char c)
{
    return c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == '_';
}

bool Scanner::isAlphaNumeric(char c)
{
    return isDigit(c) || isAlpha(c);
}

void Scanner::readIdentifier()
{
    while (isAlphaNumeric(this->peek())) this->advance();

    const auto text = this->code.substr(this->start,
        this->current - this->start);

    if (keywords.contains(text))
        this->addToken(keywords[text]);
    else
        this->addToken(TokenType::Identifier);
}
