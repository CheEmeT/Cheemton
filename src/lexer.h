
#ifndef CHEEMTON_LEXER_H
#define CHEEMTON_LEXER_H

#include <string>

enum TokenType{
    NUMBER,
    PARANTHES_OPEN,
    PARANTHES_CLOSED,
};

class Token{
private:
    TokenType type_;
    std::string data_;
public:
    Token(TokenType type, std::string data);
    Token(TokenType type);

    TokenType getType(){ return type_; }

    std::string getData(){ return data_ ;
    }
};

class Lexer{


};

#endif //CHEEMTON_LEXER_H
