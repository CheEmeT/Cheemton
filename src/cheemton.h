#ifndef CHEEMTON
#include "lexer.h"

//Number,
//Variable,
//Plus,
//Minus,
//Multiply,
//Divide,
//LeftParentheses,
//RightParentheses


namespace cheemton {
	std::string nodeArrayToString(const std::vector<Node> &array) {
		std::string result{};
		for (int i = 0; i < array.size(); i++) {
			const Node& node = array[i];
			switch (node.type)
			{
			case Number:
				result.append("[Number " + node.data + "]");
				break;
			case Variable:
				result.append("[Variable " + node.data + "]");
				break;
			case Plus:
				result.append("[Plus]");
				break;
			case Minus:
				result.append("[Minus]");
				break;
			case Multiply:
				result.append("[Multiply]");
				break;
			case Divide:
				result.append("[Divide]");
				break;
			case LeftParentheses:
				result.append("[LeftParentheses]");
				break;
			case RightParentheses:
				result.append("[RightParentheses]");
				break;

			default:
				break;
			}
			result.push_back(' ');
		}
		return result;
	}
}
#endif // !CHEEMTON
