#pragma once
#ifndef CHEEMTON_LEXER
#define CHEEMTON_LEXER

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#if _MSC_VER
#include <format>
#else
#include <fmt/format.h>
#endif

namespace cheemton {


	struct Lexeme {
		enum LexemeType {
			//TODO: Number Types
			Number,
			//------------------
			Plus,
			Minus,
			Multiply,
			Divide, 

			Variable,
			LeftParentheses,
			RightParentheses
		};
		LexemeType type;
		std::string data;
	};


	class Lexer {
	public:
		Lexer() = default;
		std::vector<Lexeme> analyzeString(const std::string &inputString);
		std::vector<Lexeme> analyzeString(const std::string &inputString, std::string* errorOutput);
	private:
	};

}
#endif
