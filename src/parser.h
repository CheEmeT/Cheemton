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

#include <memory>
#include "lexer.h"


/*
		Gramma
	STATEMENT -> EXPRESION

	EXPRESSION -> TERM '+' EXPRESSION  
	EXPRESSION -> TERM '-' EXPRESSION
	EXPRESSION -> TERM

	TERM -> FACTOR '*' TERM  
	TERM -> FACTOR '/' TERM  
	TERM -> FACTOR

	FACTOR -> '('EXPRESSION')'
	FACTOR -> NUMBER

*/

namespace cheemton {


	struct TokenNode {
		enum NodeType {
			Number,
			Plus,
			Minus,
			Multiply,
			Divide,
		};

		std::unique_ptr<TokenNode> left;
		std::unique_ptr<TokenNode> right;
		std::string data;
		NodeType type;
	};

	class Parser {
	public:
		Parser(const std::vector<Lexeme>& inputLexeme);

		int parseArithmetic();
		std::unique_ptr<TokenNode> getAST();

		bool hasError() { return m_errors.size() > 0; }
		const std::string& getErrorMessage() { return m_errors; }
	private:
		void addError(std::string msg) { m_errors.append("[PARSER][ERROR] " + msg + '\n'); }
		//Returns next lexeme if possible. Otherwise returns nullptr;
		const Lexeme* getNextLexeme() { if (m_current_lexeme < m_end_lexeme) return m_current_lexeme + 1; return nullptr; };
		//Returns current lexeme if it is in range. Otherwise returns nullptr;
		const Lexeme* getCurrentLexeme() { if (m_current_lexeme >= m_start_lexeme && m_current_lexeme <= m_end_lexeme) return m_current_lexeme; return nullptr; }
		std::unique_ptr<TokenNode> statement();
		std::unique_ptr<TokenNode> expression();
		std::unique_ptr<TokenNode> term();
		std::unique_ptr<TokenNode> factor();
		std::unique_ptr<TokenNode> number();

	private:
		std::string m_errors;
		const Lexeme* m_start_lexeme;
		const Lexeme* m_end_lexeme;
		const Lexeme* m_current_lexeme;

	};
}

#endif
