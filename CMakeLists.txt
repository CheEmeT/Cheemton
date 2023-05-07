cmake_minimum_required(VERSION 3.22)
project(Cheemton)

set(CMAKE_CXX_STANDARD 20)
message("Cmake strted")

add_executable(Cheemton "src/main.cpp" "src/lexer.cpp" "src/parser.cpp" "src/utils.cpp" "src/lexer.h" "src/utils.h" "src/parser.h" "src/cheemton.h" )
