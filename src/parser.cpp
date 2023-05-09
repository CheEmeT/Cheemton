#include "parser.h"
#include "utils.h"




using namespace cheemton;


cheemton::Parser::Parser(const std::vector<Lexeme>& inputLexeme) :
	m_start_lexeme(nullptr), m_end_lexeme(nullptr), m_current_lexeme(nullptr)
{
	if (inputLexeme.empty()) {
		m_errors.append("[PARSER] Nothing to parse.");
		return;
	}
	m_start_lexeme = &inputLexeme[0];
	m_current_lexeme = m_start_lexeme - 1;
	m_end_lexeme = &inputLexeme[inputLexeme.size() - 1];
}

int cheemton::Parser::parseArithmetic()
{
	return 0;
}

std::unique_ptr<TokenNode> cheemton::Parser::getAST()
{
	return statement();
}

std::unique_ptr<TokenNode> cheemton::Parser::statement()
{
	return expression();
}

std::unique_ptr<TokenNode> cheemton::Parser::expression()
{
	std::unique_ptr<TokenNode> result = std::make_unique<TokenNode>();

	m_current_lexeme = getNextLexeme();
	if (m_current_lexeme)
	{
		result->left = term();
		if (!result->left)
		{
			result.reset();
			return result;
		}
	}
	else
	{
		addError("Expected expression but got nothing.");
		result.reset();
		return result;
	}

	const Lexeme* check_lexeme = getNextLexeme();
	if (!check_lexeme) {
		result = std::move(result->left);
		return result;
	}

	if (check_lexeme->type == Lexeme::Plus)
	{
		result->type = TokenNode::Plus;
		m_current_lexeme = getNextLexeme();
		result->right = expression();
		if (!result->right)
		{
			result.reset();
		}
	}
	else if (check_lexeme->type == Lexeme::Minus)
	{
		result->type = TokenNode::Minus;
		m_current_lexeme = getNextLexeme();
		result->right = expression();
		if (!result->right)
		{
			result.reset();
		}
	}
	else {
		result = std::move(result->left);
	}

	

	return std::move(result);
}

std::unique_ptr<TokenNode> cheemton::Parser::term()
{
	std::unique_ptr<TokenNode> result = std::make_unique<TokenNode>();

	//m_current_lexeme = getNextLexeme();
	if (m_current_lexeme)
	{
		result->left = factor();
		if (!result->left)
		{
			result.reset();
			return std::move(result);
		}
	}
	else
	{
		addError("Expected term but got nothing.");
		result.reset();
		return std::move(result);
	}

	const Lexeme* check_lexeme = getNextLexeme();
	if (!check_lexeme) {
		result = std::move(result->left);
		return std::move(result);
	}

	if (check_lexeme->type == Lexeme::Multiply)
	{
		result->type = TokenNode::Multiply;
		m_current_lexeme = check_lexeme;
		m_current_lexeme = getNextLexeme();
		result->right = term();
		if (!result->right)
		{
			result.reset();
		}
	}
	else if (check_lexeme->type == Lexeme::Divide)
	{
		result->type = TokenNode::Divide;
		m_current_lexeme = check_lexeme;
		m_current_lexeme = getNextLexeme();
		result->right = term();
		if (!result->right)
		{
			result.reset();
		}
	}
	else {
		result = std::move(result->left);
	}
	//else {
	//	addError("Expected multiply or divide but got " + lexemeToString(*m_current_lexeme));
	//	result.reset();
	//	return std::move(result);
	//}



	return std::move(result);
}

std::unique_ptr<TokenNode> cheemton::Parser::factor()
{
	std::unique_ptr<TokenNode> result = std::make_unique<TokenNode>();

	//m_current_lexeme = getNextLexeme();
	if (!m_current_lexeme) {
		result.reset();
		return std::move(result);
	}

	if (m_current_lexeme->type == Lexeme::Number) {
		result = number();
		return result;
	}
	else if (m_current_lexeme->type == Lexeme::LeftParentheses){
		result = std::move(expression());

		m_current_lexeme = getNextLexeme();
		if (!m_current_lexeme) {
			addError("')' expected but got the end of array.");
			result.reset();
			return std::move(result);
		}

		if (m_current_lexeme->type != Lexeme::RightParentheses) {
			addError("')' expected but got " + lexemeToString(*m_current_lexeme));
			result.reset();
			return std::move(result);
		}

		return std::move(result);

	}
	else {
		addError("Number or '(' expected but got " + lexemeToString(*m_current_lexeme));
		result.reset();
		return std::move(result);
	}
}

std::unique_ptr<TokenNode> cheemton::Parser::number()
{
	std::unique_ptr<TokenNode> result = std::make_unique<TokenNode>();
	result->type = TokenNode::Number;
	result->data = m_current_lexeme->data;
	return std::move(result);
}

