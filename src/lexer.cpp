#include "lexer.h"



#if _MSC_VER
using std::format;
#else
using fmt::format;
#endif

namespace cheemton {

	std::vector<Lexeme> Lexer::analyzeString(const std::string& inputString)
	{
		std::vector<cheemton::Lexeme> result;
		std::string error;
		result = analyzeString(inputString, &error);
		std::cout << error;
		return result;
	}

	std::vector<cheemton::Lexeme> Lexer::analyzeString(const std::string& inputString, std::string* errorOutput)
	{
		std::istringstream inputStream{ inputString };

		std::vector<Lexeme> result{};
		result.reserve(inputString.size() / 2);

		int line = 0;
		int position = 0;

		char c;
		while ((c = inputStream.get()) != EOF)
		{
			position++;
			if (isblank(c))
				continue;
			if (c == '\n') {
				line++;
				position = 0;
				continue;
			}
			if (isdigit(c)) {
				Lexeme& node = result.emplace_back(Lexeme::LexemeType::Number, "");
				node.data.push_back(c);
				while (isdigit((c = inputStream.get())))
				{
					node.data.push_back(c);
				}
				inputStream.putback(c);
				continue;
			}
			switch (c)
			{
			case '(':
				result.emplace_back(Lexeme::LexemeType::LeftParentheses, "");
				break;
			case ')':
				result.emplace_back(Lexeme::LexemeType::RightParentheses, "");
				break;
			case '+':
				result.emplace_back(Lexeme::LexemeType::Plus, "");
				break;
			case '-':
				result.emplace_back(Lexeme::LexemeType::Minus, "");
				break;
			case '*':
				result.emplace_back(Lexeme::LexemeType::Multiply, "");
				break;
			case '/':
				result.emplace_back(Lexeme::LexemeType::Divide, "");
				break;
			default:
				errorOutput->append(format("[ERROR][LEXER] [{}:{}] Unknown character \'{}\'", line, position, c));
				return std::vector<Lexeme>{};
			}
		}

		return result;
	}

}