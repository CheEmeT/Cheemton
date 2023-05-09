#include "utils.h"
#include <stack>
#include <sstream>

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

std::string cheemton::tokenNodeToString(const TokenNode& token)
{
	switch (token.type)
	{
	case TokenNode::Number:		return "Number" + token.data;
	case TokenNode::Plus:		return "Plus";
	case TokenNode::Minus:		return "Minus";
	case TokenNode::Multiply:	return "Multiply";
	case TokenNode::Divide:		return "Divide";
	default:
		return "no_type";
	}

}

std::string cheemton::tokenTreeToGrapvizFile(const TokenNode* root)
{
	std::stringstream result;

	std::stack<const TokenNode*> nodes{};
	nodes.push(root);


	result << ("graph TREE{\n");
	result << "\t" << tokenNodeToString(*root) << root << "[label = " << tokenNodeToString(*root) << "]\n";

	while (!nodes.empty())
	{
		const TokenNode* node = nodes.top();
		nodes.pop();

		if (node->left) {
			nodes.push(node->left.get());
			result << "\t" << tokenNodeToString(*node->left) << node->left.get() << "[label = " << tokenNodeToString(*node->left) << "]\n";
			result << "\t" << tokenNodeToString(*node) << node << " -- " << tokenNodeToString(*node->left) << node->left.get() << "\n";
		}

		if (node->right) {
			nodes.push(node->right.get());
			result << "\t" << tokenNodeToString(*node->right) << node->right.get() << "[label = " << tokenNodeToString(*node->right) << "]\n";
			result << "\t" << tokenNodeToString(*node) << node << " -- " << tokenNodeToString(*node->right) << node->right.get() << "\n";
		}
	}

	result << "}";

	return result.str();
}
