//
// Created by sascha-roggatz on 02.10.24.
//

#include <string_view>
#include <vector>
#include "../Token/Token.cpp"

class Scanner {
public:
    static std::vector<Token> scantTokens(const std::string_view& source );
};
