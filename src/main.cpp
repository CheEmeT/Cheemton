#include "cheemton.h"
#include <exception>


int main(int argc, char** argv) {
	std::cout << "Starting program\n";
	std::string str("32 + 38 -    d ******    \n (3444445 * 23 - 4)");
	cheemton::Lexer lexer;
	try {
		auto a = lexer.analyzeString(str);
		if(a)
			std::cout << nodeArrayToString(*a);
	}
	catch (std::exception e) {
		std::cout << "Error happened\n" << e.what();
	}
}