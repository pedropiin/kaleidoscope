cmake_minimum_required(VERSION 3.13)

project(kaleidoscope)

set(CMAKE_CXX_STANDARD 20)

add_executable(kaleidoscope ./src/main.cpp ./src/lexer.cpp ./src/ast.cpp ./src/parser.cpp)

