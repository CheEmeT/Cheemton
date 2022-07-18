cmake_minimum_required(VERSION 3.22)
project(Cheemton)

set(CMAKE_CXX_STANDARD 20)

file(GLOB src_ RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*)
message(${src_})

add_executable(Cheemton
        ${src_})
