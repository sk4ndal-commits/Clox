#include <iostream>
#include <filesystem>
#include <fstream>
#include "Interpreter/Interpreter.h"

int main(int argc, char *argv[]) {

    if (argc <= 1) {
        std::cerr << "Error: No file provided" << std::endl;
        return 1;
    }

    std::string fileName = argv[1];
    if (!std::filesystem::exists(fileName)) {
        std::cerr << "Error: The file: " << fileName << " does not exist" << std::endl;
        return 1;
    }

    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: The file " << fileName << " cannot be opened" << std::endl;
        return 1;
    }

    Interpreter::runFile(file);

    return 0;
}
