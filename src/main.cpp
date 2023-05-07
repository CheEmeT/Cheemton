#include "cheemton.h"

#include <exception>



int main(int argc, char** argv) {
	std::cout << "Starting program\n";
	std::string str("(4 + 3) - (4)");
	cheemton::Lexer lexer;

	try {
		std::cout << "Source code: " << str << "\n\n";

		std::vector<cheemton::Lexeme>* a = lexer.analyzeString(str);
		std::cout << "Lexemes:\n";
		if (a) {
			std::cout << lexemeArrayToString(*a);
			cheemton::Parser parser(*a);
			std::cout << "\n\n" << "ABS output:\n";

			cheemton::Node* Tree = parser.getAST();
			if (parser.hasError()) {
				std::cout << "\n\nParsing errors:\n" << parser.getErrorMessage();
			}
		}
	}
	catch (std::exception e) {
		std::cout << "Error happened\n" << e.what();
	}


}