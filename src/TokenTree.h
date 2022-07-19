#ifndef CHEEMTON_TOKENTREE_H
#define CHEEMTON_TOKENTREE_H

#include <vector>
#include <memory>
#include "lexer.h"
namespace  cheemton{
    class TokenTreeNode{
    private:
        TokenTreeNode* parent_;
        Token token_;
        std::vector<std::unique_ptr<TokenTreeNode>> children_;
    public:
        TokenTreeNode(Token const & token, TokenTreeNode const * parent = nullptr):
            children_(2),
            token_(token)
            {}

        void addChild(std::unique_ptr<TokenTreeNode> &child ){

            //children_.push_back(std::move(child));
        }

    };

    class TokenTree{
    private:
        TokenTreeNode start_;
    public:
        TokenTree(TokenTreeNode  &start): start_(start){}
    };


}



#endif //CHEEMTON_TOKENTREE_H
