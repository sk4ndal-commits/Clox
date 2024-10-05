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
    void addToken(TokenType type);
};
