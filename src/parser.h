#ifndef CHEEMTON_PARSER_H
#define CHEEMTON_PARSER_H


#include <vector>
#include <memory>
#include "lexer.h"
namespace  cheemton{

    class TokenTreeNode{
    private:
        Token const * token_;
        std::vector<std::unique_ptr<TokenTreeNode>> children_;
    public:
        explicit TokenTreeNode(Token const * token):
            token_(token)
            {}
#if 0
        TokenTreeNode(TokenTreeNode&& other) noexcept:
            token_(std::move(other.token_)),
            children_(std::move(other.children_)),
            parent_(other.parent_){
                    for(auto &child : children_){
                    }
        }

        TokenTreeNode& operator= (TokenTreeNode&& other) noexcept{
            token_ = std::move(other.token_);
            children_ = std::move(other.children_);
            for(auto &child : children_){
            }
            return *this;
        }
#endif
        auto const & getChildren() const{return children_;}
        Token const & getToken() const{ return *token_; }

        //Important to rvalue!
        void addChild(std::unique_ptr<TokenTreeNode> &&child ){
            children_.push_back(std::move(child));
        }

    };

    std::ostream & operator<<(std::ostream& ostream, TokenTreeNode const & node){
        ostream << "(";
        ostream << node.getToken();
        for(auto &ref : node.getChildren()){
            ostream << *ref << ", ";
        }
        ostream << ")";
        return ostream;
    }
    //TODO: Refactor parser
    class Parser{
    private:
        std::unique_ptr<TokenTreeNode> start_;
        using tokenIter = std::vector<std::unique_ptr<Token>>::iterator;
        std::vector<std::unique_ptr<Token>> tokens_;


        /*Gramma:
        * F: (F)F | E | null
        * E: D ± F | D
        * D: T \* D | T
        * T: number | (F)
        */
        TokenTreeNode* parseF(tokenIter begin, tokenIter end){
            if(begin->get()->getType() == TokenType::PARENTHES_OPEN && (end - 1)->get()->getType() == TokenType::PARENTHES_CLOSED)
               return parseE(begin + 1, end - 1);
            return parseE(begin, end);

        }

        TokenTreeNode* parseE(tokenIter begin, tokenIter end){
            TokenTreeNode* ptr;
            for(auto t = begin; t < end; ++t){
                auto type = t->get()->getType();
                if(type == TokenType::OP_PLUS || type == TokenType::OP_MINUS){
                    ptr = new TokenTreeNode(t->get());
                    //TODO: Show line and char location
                    if (t == begin){
                        std::stringstream stream;
                        stream << "[PARSER] Expression was expected, got " << *(t->get());
                        throw std::runtime_error(stream.str());
                    }
                    if (t + 1 == end){
                        std::stringstream stream;
                        stream << "[PARSER] Unexpected token " << *(t->get());
                        throw std::runtime_error(stream.str());
                    }
                    ptr->addChild(std::unique_ptr<TokenTreeNode>(parseD(begin, t)));
                    ptr->addChild(std::unique_ptr<TokenTreeNode>(parseF(t + 1, end)));
                    return ptr;
                }
            }
            return parseD(begin, end);
        }

        TokenTreeNode* parseD(tokenIter begin, tokenIter end){
            TokenTreeNode* ptr;
            for(auto t = begin; t < end; ++t){
                auto type = t->get()->getType();
                if(type == TokenType::OP_MULT || type == TokenType::OP_DIV){
                    ptr = new TokenTreeNode(t->get());
                    //TODO: Show line and char location
                    if (t == begin){
                        std::stringstream stream;
                        stream << "[PARSER] Expression was expected, got " << *(t->get());
                        throw std::runtime_error(stream.str());
                    }
                    if (t + 1 == end){
                        std::stringstream stream;
                        stream << "[PARSER] Unexpected token " << *(t->get());
                        throw std::runtime_error(stream.str());
                    }
                    ptr->addChild(std::unique_ptr<TokenTreeNode>(parseT(begin, t)));
                    ptr->addChild(std::unique_ptr<TokenTreeNode>(parseD(t + 1, end)));
                    return ptr;
                }
            }
            return parseT(begin, end);
        }

        TokenTreeNode* parseT(tokenIter begin, tokenIter end){
            TokenTreeNode* ptr;
            if(begin + 1 == end){
                if(begin->get()->getType() == TokenType::NUMBER)
                    return new TokenTreeNode(begin->get());
                std::stringstream stream;
                stream << "[PARSER] Number was exoected got " << *(begin->get());
                throw std::runtime_error(stream.str());
            }
            if(begin->get()->getType() == TokenType::PARENTHES_OPEN && (end - 1)->get()->getType() == TokenType::PARENTHES_CLOSED)
                return parseE(begin + 1, end - 1);
            throw std::runtime_error("[PARSER] You messed with parentheses");
        }

    public:
        Parser(std::vector<std::unique_ptr<Token>> &&tokens):
        tokens_(std::move(tokens)){}

        TokenTreeNode* getTokenTree(){
            start_ = std::unique_ptr<TokenTreeNode>(parseF(tokens_.begin(), tokens_.end()));
            return start_.get();
        }
    };


}



#endif //CHEEMTON_PARSER_H
