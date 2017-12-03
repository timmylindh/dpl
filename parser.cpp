/*
 * Parser.cpp
 *
 *  Created on: 13 nov. 2017
 *      Author: timmy.lindholm
 */

#include <stack>
#include <iostream>

#include "parser.h"
#include "lexer.h"
#include "error.h"

// Defines an operator with correct precedence
typedef struct {
	char * name;
	int precedence;
} Operator;

Parser::Parser() {

	this->lexer = new Lexer;
	this->buffer = NULL;
	this->global_program = NULL;
	this->program = NULL;
}

/*
 * Parses the code which resides in buffer
 * May be called recursively, thus the non-static program
 * pointer
*/
void Parser::parse(Program * program) {
	Token * tok;

	this->program = program;
	tok = lexer->next_token();

	// Entry points for keywords and instructions
	switch(tok->type) {

	// Function or variable name
	case TOK_NAME:
		const char * name;

		name = tok->value;
		tok = lexer->next_token();

		// Assignment operation
		if(IS_ASSIGNMENT(tok->type)) {
			parse_assignment_operation(name, tok->type);
		}

		// Function call
		else if(tok->type == TOK_RIGHT_PAR);

		break;

	// If or else if
	case TOK_IF:
	case TOK_ELSE_IF:
		break;

	// While loop
	case TOK_WHILE:
		break;

	// For all
	case TOK_UNI_QUANT:
		break;

	}
}

// Parse an assignment operation and create the corresponding memory layout
void Parser::parse_assignment_operation(const char * name, int assign_type) {

}

// Convert infix expression to postfix expression for convenience
// and determine the type of the expression
std::vector<Token *> * Parser::parse_expression(int &type) {
	Token * tok;
	std::stack<Token *> op_stack;
	std::vector<Token *> * expression;

	expression = new std::vector<Token *>;

	// Loop through tokens until dot or end of line
	tok = lexer->next_token();

	while(tok->type != TOK_DOT && tok->type != TOK_COMMA && tok->type != TOK_NULL) {

		// Numeric operand
		if(tok->type == TOK_INT || tok->type == TOK_FLOAT) {
			expression->push_back(tok);
		}

		// Function or variable operand
		else if(tok->type == TOK_NAME) {
			auto func_name = tok->value;
			tok = lexer->next_token();

			// Function
			if(tok->type == TOK_LEFT_PAR) {
				auto func = parse_function_call(func_name);
			}
		}
	}

}

/* Parse a call to a function, output an error if function for some reason
 * does not exist or have matches with arguments
 */
Function * Parser::parse_function_call(const char * func_name) {
	Function * func;

	// Try to fetch function
	func = global_program->get_function(func_name);

	// Means function could not be found in program map
	if(! func)
		ERROR(T_CRIT, "unknown call to function %s, on line %d.", func_name, lexer->n_lines);

	// Get function arguments
	while(lexer->last_token->type != TOK_RIGHT_PAR && lexer->last_token->type != TOK_NULL) {
		auto arg = func->get_next_argument();
		int type;

		// Unexpected argument
		if(! arg)
			ERROR(T_CRIT, "unknown argument %s in call to function %s, on line %d.", lexer->last_token->value, func_name, lexer->n_lines);

		arg->value = parse_expression(type);
		arg->type = type;
	}

	// No closing right paranthesis
	if(lexer->last_token->type == TOK_NULL)
		ERROR(T_CRIT, "unexpected end of function %s on line %d.", func_name, lexer->n_lines);

	// Push function call to program instruction queue
	program->push_instruction(new FunctionCall(func));
	return func;
}

// Calls the main parse function with the global program as argument
Program * Parser::parse() {
	global_program = new GlobalProgram;

	this->parse(global_program);

	return global_program;
}

/*
 * Sets the internal code buffer to the argument
 * This way we do not have to pass the buffer to the lexer
 * Each call.
 */
void Parser::set_input_code(char * buffer) {
	this->buffer = buffer;
	this->lexer->set_input_code(buffer);
}
