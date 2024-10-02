//
// Created by sascha-roggatz on 02.10.24.
//

#include <string_view>
#include <vector>
#include "../Token/Token.cpp"

class Scanner {
private:
    int current;
public:
    static std::vector<Token> scantTokens(const std::string_view &source);

    static char advance(int &current, const std::string_view &source);

    static void addFullToken(
            std::vector<Token> &tokens,
            TokenType type,
            const std::string_view &source,
            int start,
            int current,
            int line);
};
