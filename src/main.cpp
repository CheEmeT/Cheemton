#include "cheemton.h"

#include <exception>
#include <fstream>



int main(int argc, char** argv) {
	std::cout << "Starting program\n";
	std::string str("(4 * 6 - 7 / 3) - 8 * ( 4 - 3  )");
	cheemton::Lexer lexer;

	try {
		std::cout << "Source code: " << str << "\n\n";

		std::vector<cheemton::Lexeme> a = lexer.analyzeString(str);
		std::cout << "Lexemes:\n";
		std::cout << lexemeArrayToString(a);
		cheemton::Parser parser(a);

		auto Tree = parser.getAST();
		if (parser.hasError()) {
			std::cout << "\n\nParsing errors:\n" << parser.getErrorMessage();
		}
		else {
			std::ofstream graph{ "graph.gv" };
			if (graph.is_open()) {
				graph << cheemton::tokenTreeToGrapvizFile(Tree.get());
			}
			else
				std::cout << "Failed to open graph file.";

		}

	}
	catch (std::exception e) {
		std::cout << "Error happened\n" << e.what();
	}


}