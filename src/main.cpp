#include <iostream>
#include "lexer.h"
#include "parser.h"

int main() {
    std::string code = "(2 + 1) * 3 - 3\n";
    cheemton::Lexer lexer(code);
    auto v = lexer.getTokens();
    for(auto & ref : v){
        std::cout << *ref << std::endl;
    }
    //cheemton::Parser parser(std::move(v));
    //std::cout << *parser.getTokenTree();



    return 0;
}
