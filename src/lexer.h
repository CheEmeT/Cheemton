#ifndef CHEEMTON_LEXER
#define CHEEMTON_LEXER

#include <iostream>
#include <sstream>
#include <string>
#include <format>
#include <vector>


namespace cheemton {
	enum NodeType {
		//TODO: Number Types
		Number,
		//------------------
		Variable,
		Plus,
		Minus,
		Multiply,
		Divide,
		LeftParentheses,
		RightParentheses
	};

	struct Node {
		NodeType type;
		std::string data;
	};


	class Lexer {
	public:
		Lexer() = default;
		std::vector<Node>* analyzeString(const std::string &inputString);
		std::vector<Node>* analyzeString(const std::string &inputString, std::string* errorOutput);
	private:
	};

}
#endif
