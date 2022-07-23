
#ifndef CHEEMTON_LEXER_H
#define CHEEMTON_LEXER_H

#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <memory>
#include <exception>

namespace cheemton {


    enum TokenType {
        NUMBER,
        OP_PLUS,
        OP_MINUS,
        OP_MULT,
        OP_DIV,
        PARENTHES_OPEN,
        PARENTHES_CLOSED,
    };


    class Token {
    private:
        TokenType type_;

    public:
        Token(TokenType type) : type_(type) {}
        TokenType getType() const{ return type_; }
    };

    class NumberToken: public Token{
    private:
        int number_;
    public:
        NumberToken(int num): Token(TokenType::NUMBER),number_(num){}
        int getNumber() const {return number_;}
    };

    std::ostream& operator<< (std::ostream& ostream, const Token& token){
        switch (token.getType()) {
            case TokenType::NUMBER:
                ostream << "[NUM]: " << static_cast<NumberToken const &>(token).getNumber();
                break;
            case TokenType::PARENTHES_OPEN:
                ostream << "[PTHS O]";
                break;
            case TokenType::PARENTHES_CLOSED:
                ostream << "[PTHS C]";
                break;
            case TokenType::OP_MINUS:
                ostream << "[OP -]";
                break;
            case TokenType::OP_PLUS:
                ostream << "[OP +]";
                break;
            case TokenType::OP_MULT:
                ostream << "[OP *]";
                break;
            case TokenType::OP_DIV:
                ostream << "[OP /]";
                break;

        }
        return ostream;
    }

    class Lexer {
    private:
        std::string code_;

        int cur_line_ = 0;
        int cur_char_ = 0;

        int getInt(std::stringstream &str){
            int i;
            str >> i;
            return i;
        }

    public:
        Lexer(std::string code):
            code_(std::move(code)){};
        /*
         * Alphabet:
         *          spaces      ' ', '\n', '\t', '\r'
         *          parentheses '(', ')'
         *          arithmetic  '+', '-'
         *          digits      '0' - '9'
        */
        std::vector<std::unique_ptr<Token>> getTokens() {
            std::vector<std::unique_ptr<Token>> ret; //TODO: Estimate size
            std::stringstream stream(code_,  std::ios_base::in );

            char c;
            while(!stream.get(c).eof()){
                cur_char_++;
                switch (c) {
                    case '(':
                        ret.emplace_back(new Token(TokenType::PARENTHES_OPEN));
                        break;
                    case ')':
                        ret.emplace_back(new Token(TokenType::PARENTHES_CLOSED));
                        break;
                    case '+':
                        ret.emplace_back(new Token(TokenType::OP_PLUS));
                        break;
                    case '-':
                        ret.emplace_back(new Token(TokenType::OP_MINUS));
                        break;
                   case '*':
                        ret.emplace_back(new Token(TokenType::OP_MULT));
                        break;
                    case '/':
                        ret.emplace_back(new Token(TokenType::OP_DIV));
                        break;
                    case '\n':
                        cur_line_++;
                        cur_char_ = 0;
                    case ' ':
                    case '\r':
                    case '\t':
                        break;
                    default:
                        if(std::isdigit(c)){
                            stream.unget();
                            ret.emplace_back(new NumberToken(getInt(stream)));
                            break;
                        }else{
                            std::stringstream msg;
                            msg << "[LEXER] Unexpected character '" << c << "' at " << cur_line_ << ":" << cur_char_;
                            throw std::runtime_error(msg.str());
                        }
                }
            }
            return ret;
        }
    };
}
#endif //CHEEMTON_LEXER_H
