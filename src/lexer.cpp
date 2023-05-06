#include "lexer.h"

using namespace cheemton;


std::vector<Node>* Lexer::analyzeString(const std::string& inputString)
{
	std::vector<cheemton::Node>* result;
	std::string error;
	result = analyzeString(inputString, &error);
	std::cout << error;
	return result;
}

std::vector<cheemton::Node>* Lexer::analyzeString(const std::string &inputString, std::string* errorOutput)
{
	std::istringstream inputStream{inputString};

	std::vector<Node> *result = new std::vector<Node>{};
	result->reserve(inputString.size() / 2);

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
			Node &node = result->emplace_back(NodeType::Number, "");
			node.data.push_back(c);
			while (isdigit( (c = inputStream.get())) )
			{
				node.data.push_back(c);
			}
			inputStream.putback(c);
			continue;
		}
		switch (c)
		{
		case '(':
			result->emplace_back(NodeType::LeftParentheses, "");
			break;
		case ')':
			result->emplace_back(NodeType::RightParentheses, "");
			break;
		case '+':
			result->emplace_back(NodeType::Plus, "");
			break;
		case '-':
			result->emplace_back(NodeType::Minus, "");
			break;
		case '*':
			result->emplace_back(NodeType::Multiply, "");
			break;
		case '/':
			result->emplace_back(NodeType::Divide, "");
			break;
		default:
			errorOutput->append(std::format("[LEXER] [{}:{}] Unknown character \'{}\'", line, position, c));
			delete result;
			return nullptr;
		}
	}

	return result;
}
