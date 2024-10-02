//
// Created by sascha-roggatz on 26.09.24.
//

#include <string>
#include "../Scanner/Scanner.h"

class Interpreter {
public:
    static void runFile(const std::ifstream & file);

private:
    static void run(const std::string_view& source );
};