cmake_minimum_required(VERSION 3.29)
project(Clox)

set(CMAKE_CXX_STANDARD 23)

add_executable(Clox main.cpp
        Interpreter/Interpreter.h
        Interpreter/Interpreter.cpp
        Scanner/Scanner.h
        Scanner/Scanner.cpp
        Token/Token.cpp
        Enums/TokenType.cpp
)
