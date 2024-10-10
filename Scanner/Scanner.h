//
// Created by sascha-roggatz on 02.10.24.
//

#include <string_view>
#include <vector>
#include "../Token/Token.cpp"

class Scanner {
private:
    int current;
    int start;
    int line;
    std::vector<Token> tokens;
    std::string_view code;
public:
    Scanner();

    ~Scanner();

    std::vector<Token> scanTokens(const std::string_view &source);

    void scanToken();

    char advance();

    char peek();

    char peekNext();

    void addToken(TokenType type);

    void addToken(TokenType type, const std::any& literal);

    void readString();

    void readNumber();

    void readIdentifier();

    bool isAtEnd();

    bool nextCharMatches(char  expected);

    static bool isDigit(char c);

    static bool isAlpha(char c);

    static bool isAlphaNumeric(char c);

    static void initializeKeywords();
};
