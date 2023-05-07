#ifndef CHEEMTON_UTILS
#define CHEEMTON_UTILS
#include "lexer.h"

namespace cheemton {
	std::string lexemeToString(const Lexeme& lexeme);
	std::string lexemeArrayToString(const std::vector<Lexeme>& array);
}


#endif // !CHEEMTON_UTILS