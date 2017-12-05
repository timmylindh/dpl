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

	while(tok->type != TOK_NULL) {
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

		tok = lexer->next_token();
	}
}

// Parse an assignment operation and create the corresponding memory layout
void Parser::parse_assignment_operation(const char * name, int assign_type) {
	std::vector<Token *> * expression;
	int type;

	// Get the expression
	expression = parse_expression(type);

	for(auto x : *expression) {
		std::cout << x->value;
	}

	std::cout << std::endl;

	// Create the variable and add it to the current program
	Variable * variable = new Variable(name, expression, type);
	program->push_variable(variable);

	// Create assignment instruction
	Assignment * assignment = new Assignment(variable, assign_type);
	program->push_instruction(assignment);
}

// Convert infix expression to postfix expression for convenience
// and determine the type of the expression
std::vector<Token *> * Parser::parse_expression(int &type) {
	Token * tok;
	std::stack<Token *> op_stack;
	std::vector<Token *> * expression;
	std::unordered_map<int, int> operators;

	operators[TOK_MULT] = 3;
	operators[TOK_DIV] = 3;
	operators[TOK_PLUS] = 2;
	operators[TOK_MINUS] = 2;
	operators[TOK_LEFT_PAR] = 1;

	expression = new std::vector<Token *>;
	type = TOK_NULL;

	// Loop through tokens until dot or end of line
	tok = lexer->next_token();

	while(tok->type != TOK_DOT && tok->type != TOK_COMMA && tok->type != TOK_NULL) {

		// Numeric operand
		if(tok->type == TOK_INT || tok->type == TOK_FLOAT) {
			if(tok->type == TOK_FLOAT)
				type = TOK_FLOAT;
			else if(tok->type == TOK_INT && type != TOK_FLOAT && type != TOK_STRING)
				type = TOK_INT;

			expression->push_back(tok);
		}

		// String operand
		else if(tok->type == TOK_STRING) {
			type = TOK_STRING;
			expression->push_back(tok);
		}

		// Function or variable operand
		else if(tok->type == TOK_NAME) {
			Token * name = tok;
			tok = lexer->next_token();

			// Function
			if(tok->type == TOK_LEFT_PAR) {
				auto func = parse_function_call(name->value);

				// Check if function has a certain return type
				if(type != TOK_NULL) {
					if((! func->check_return_type(type)) && type != TOK_STRING)
						ERROR(T_CRIT, "invalid return value of function %s on line %d.", name->value, lexer->n_lines);
				}

				else
					type = func->get_return_type();

				expression->push_back(new Token((char * const) "@", TOK_AT));
			}

			// Variable
			else {
				auto var = program->get_variable(name->value);

				// Determine if variable exists
				if(! var)
					ERROR(T_CRIT, "undefined variable %s on line %d.", name->value, lexer->n_lines);

				// Determine variable type
				if(type != TOK_NULL) {
					if(var->type != type && type != TOK_STRING)
						ERROR(T_CRIT, "invalid type of variable %s on line %d.", name->value, lexer->n_lines);
				}

				else
					type = var->type;
			}

			expression->push_back(name);
			continue;
		}

		else if(tok->type == TOK_LEFT_PAR)
			op_stack.push(tok);

		else if(tok->type == TOK_RIGHT_PAR) {
			Token * op;
			op = NULL;

			// Pop stack until corresponding left paranthesis is found
			while((! op_stack.empty()) && (op = op_stack.top())->type != TOK_LEFT_PAR) {
				expression->push_back(op);
				op_stack.pop();
			}

			// Matching paranthesis
			if(op != NULL && op->type == TOK_LEFT_PAR)
				op_stack.pop();

			else
				ERROR(T_CRIT, "faulty expression on line %d", lexer->n_lines);

		}

		// Operator
		else if(IS_OPERATOR(tok->type)) {
			Token * op;
			int prec;

			op = NULL;
			prec = operators[tok->type];

			// Add operators with higher precedence
			while(! op_stack.empty() && prec <= operators[(op = op_stack.top())->type]) {
				expression->push_back(op);
				op_stack.pop();
			}

			op_stack.push(tok);
		}

		// Invalid token
		else
			ERROR(T_CRIT, "unexpected '%s' on line %d", tok->value, lexer->n_lines);

		tok = lexer->next_token();
	}

	// Check if no ending delimiter
	if(tok->type == TOK_NULL)
		ERROR(T_CRIT, "unexpected end of file on line %d", lexer->n_lines);

	// Add remaining operators to expression
	while(! op_stack.empty()) {
		expression->push_back(op_stack.top());
		op_stack.pop();
	}

	return expression;
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
