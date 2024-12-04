#include <iostream>
#include <filesystem>
#include <fstream>
#include "Interpreter/Interpreter.h"

int main(const int argc, char *argv[]) {

    if (argc <= 1) {
        std::cerr << "Error: No file provided" << std::endl;
        return 1;
    }

    const std::string fileName = argv[1];
    if (!exists(std::filesystem::path(fileName))) {
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
