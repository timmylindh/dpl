/*
 * expression.cpp
 *
 *  Created on: 20 nov. 2017
 *      Author: eatit
 */

#include <stack>
#include <vector>

#include "lexer.h"
#include "expression.h"

namespace expr {

	// Defines an operator with correct precedence
	typedef struct {
		char * name;
		int precedence;
	} Operator;

	// Convert infix expression to postfix expression
	char * infix_to_post(std::vector<Token *> tokens) {
		std::stack<Token> op_stack;

		// Loop through tokens
		for(auto token : tokens) {
			std::cerr << token->value;
		}
	}

}




