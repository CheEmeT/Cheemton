#include "parser.h"
#include "utils.h"




using namespace cheemton;


cheemton::Parser::Parser(const std::vector<Lexeme>& inputLexeme):
	m_start(nullptr), m_end(nullptr), m_current(nullptr)
{
	if (inputLexeme.empty()) {
		m_errors.append("[PARSER] Nothing to parse.");
		return;
	}
	m_start = &inputLexeme[0];
	m_current = m_start;
	m_end = &inputLexeme[inputLexeme.size() - 1];
}

int cheemton::Parser::parseArithmetic()
{
	return 0;
}

Node* cheemton::Parser::getAST()
{
	return statement();
}

Node* cheemton::Parser::statement()
{
	Node* result = new Node{};
	result->left = expression();
	return result;
}

Node* cheemton::Parser::expression()
{
	if (!m_current) {
		m_errors.append("[ERROR][PARSER] Uncompleted string of lexemes at expression\n");
		return nullptr;
	}

	Node* result = new Node{};	
	result->left = factor();

	if (!m_current || (m_current->type != Lexeme::Plus && m_current->type != Lexeme::Minus)) {
		return result;
	}

	result->middle = new Node{};
	result->middle->type = m_current->type == Lexeme::Plus ? Node::Plus : Node::Minus;

	m_current = getNextLexeme();

	result->right = expression();

	return result;
}

Node* cheemton::Parser::factor()
{
	if (!m_current) {
		m_errors.append("[ERROR][PARSER] Uncompleted string of lexemes at term\n");
		return nullptr;
	}

	Node* result = new Node{};

	result->left = term();
	m_current = getNextLexeme();
	if (!m_current || (m_current->type != Lexeme::Multiply && m_current->type != Lexeme::Divide)) {
		return result;
	}

	result->middle = new Node{};
	result->middle->type = m_current->type == Lexeme::Multiply ? Node::Multiply : Node::Divide;


	m_current = getNextLexeme();
	result->right = expression();

	return result;
}

Node* cheemton::Parser::term()
{
	if (!m_current) {
		m_errors.append("[ERROR][PARSER] Uncompleted string of lexemes at factor\n");
		return nullptr;
	}

	Node* result = new Node{};

	if (m_current->type == Lexeme::LeftParentheses) {
		result->left = new Node{};
		result->left->type = Node::LeftParentheses;

		m_current = getNextLexeme();
		result->middle = expression();

		if (m_current->type != Lexeme::LexemeType::RightParentheses) {
			m_errors.append("[ERROR][PARSER] Expected right parantheses but got " + lexemeToString(*m_current) + '\n');
			delete result;
			return nullptr;
		}

		m_current = getNextLexeme();

		return result;
	}
	result->left = number();
	return result;
}

Node* cheemton::Parser::number()
{
	if (!m_current) {
		m_errors.append("[ERROR][PARSER] Uncompleted string of lexemes at number\n");
		return nullptr;
	}

	if (m_current->type != Lexeme::Number) {
		m_errors.append("[ERROR][PARSER] Expected a number but got " + lexemeToString(*m_current) + '\n');
		return nullptr;
	}
	Node* result = new Node{};
	result->type = Node::Number;
	result->lexeme = m_current;
	return result;
}
