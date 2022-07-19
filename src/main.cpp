#include <iostream>
#include "lexer.h"

int main() {
    std::string code = "(23 + 4 - (3 - 4)) \n      3     + 2";
    cheemton::Lexer lexer(code);
    auto arr = lexer.analyze();
    for(auto& ref : arr)
        std::cout << *ref << std::endl;


    return 0;
}
