#include "utils.h"

std::string cheemton::lexemeToString(const Lexeme& lexeme)
{
	switch (lexeme.type)
	{
	case Lexeme::LexemeType::Number:
		return("[Number " + lexeme.data + "]");
	case Lexeme::LexemeType::Variable:
		return("[Variable " + lexeme.data + "]");
	case Lexeme::LexemeType::Plus:
		return("[Plus]");
	case Lexeme::LexemeType::Minus:
		return("[Minus]");
	case Lexeme::LexemeType::Multiply:
		return("[Multiply]");
	case Lexeme::LexemeType::Divide:
		return("[Divide]");
	case Lexeme::LexemeType::LeftParentheses:
		return("[LeftParentheses]");
	case Lexeme::LexemeType::RightParentheses:
		return("[RightParentheses]");

	default:
		return "Something went wrong";
	}
}

std::string cheemton::lexemeArrayToString(const std::vector<Lexeme>& array)
{
	std::string result{};
	for (int i = 0; i < array.size(); i++) {
		result.append(lexemeToString(array[i]) + '\n');
	}
	return result;
}
