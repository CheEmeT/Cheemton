#ifndef CHEEMTON_PARSER
#define CHEEMTON_PARSER

//#ifdef CHEEMTON_DEBUG
//
//#define LOG(x) (std::cout << x << '\n');
//
//#else
//
//#define LOG(x)
//
//#endif// CHEEMTON_DEBUG

#include "lexer.h"

/*
		Gramma
	STATEMENT -> EXPRESION

	EXPRESSION -> FACTOR '+' EXPRESSION 
	EXPRESSION -> FACTOR '-' EXPRESSION 
	EXPRESSION -> FACTOR

	FACTOR -> TERM '*' EXPRESSION
	FACTOR -> TERM '/' EXPRESSION
	FACTOR -> TERM

	TERM -> '('EXPRESSION')'
	TERM -> NUMBER

*/

namespace cheemton {


	struct Node {
		enum NodeType {
			Statement,
			Expression,
			Term,
			Factor,
			Number,
			Plus,
			Minus,
			Multiply,
			Divide,
			LeftParentheses,
			RightParentheses
		};

		Node* left;
		Node* middle; 
		Node* right;
		const Lexeme* lexeme;
		NodeType type;

		~Node() {
			delete left;
			delete middle;
			delete right;
		}
	};

	class Parser {
	public:
		Parser(const std::vector<Lexeme>& inputLexeme);

		int parseArithmetic();
		Node* getAST();

		bool hasError() { return m_errors.size() > 0; }
		const std::string& getErrorMessage() { return m_errors; }
	private:
		//Returns next lexeme if possible. Otherwise returns nullptr;
		const Lexeme* getNextLexeme() { if (m_current < m_end) return m_current + 1; return nullptr; };
		Node* statement();
		Node* expression();
		Node* factor();
		Node* term();
		Node* number();

	private:
		std::string m_errors;
		const Lexeme* m_start;
		const Lexeme* m_end;
		const Lexeme* m_current;

	};
}

#endif
