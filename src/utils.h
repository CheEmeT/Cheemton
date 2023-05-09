#ifndef CHEEMTON_UTILS
#define CHEEMTON_UTILS
#include "lexer.h"
#include "parser.h"

namespace cheemton {
	std::string lexemeToString(const Lexeme& lexeme);
	std::string lexemeArrayToString(const std::vector<Lexeme>& array);

	std::string tokenNodeToString(const TokenNode& token);
	std::string tokenTreeToGrapvizFile(const TokenNode* root);
}


#endif // !CHEEMTON_UTILS