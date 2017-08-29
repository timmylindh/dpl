/*
 * DParser.cpp
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

#include <sstream>

#include "Parser.h"
#include "Instruction.h"
#include "../error/Error.h"

Parser::Parser(Lexer * lexer) {
	this->lexer = lexer;
}

Parser::~Parser() {

}

// Parse a single, or a set of instructions
d_uint Parser::parse(d_string * code, Program * program) {
	Token * tok;
	string name;

	this->program = program;
	tok = this->lexer->next_token(code);

	// Variable or function name
	switch(tok->type) {
	case TOKEN_NAME:
		name = tok->value;
		tok = this->lexer->next_token(code);

		// Assignment operation, =, *=, /= ....
		if(ASSIGN_OP(tok->type))
			this->ins_assignment(code, name, tok->type);

		// Create function operation
		else if(tok->type == TOKEN_OP_COLON)
			this->ins_function_def(code, name);

		// Else error
		else {
			ERROR(new Error(ERRNO_SYNTAX, "incorrect syntax"));
		}

		break;

	case TOKEN_CODE_END:
		return 0;

	}

	return 1;
}

// Parse an assignment instruction
void Parser::ins_assignment(d_string * code, string name, d_uint type) {
	string expr;
	I_Assignment * assignment;
	Variable * var;
	d_uint expr_type;

	expr_type = this->parse_expr(code, &expr);

	// Add assignment instruction to program tree
	assignment = new I_Assignment(this->program, INSTRUCTION_ASSIGNMENT);

	assignment->assign_type = type;
	assignment->left = name;
	assignment->right = expr;

	this->program->Instructions->push_back(assignment);

	// Add variable to program tree
	var = new Variable(name);

	var->Types->push_back(expr_type);
	var->History->push_back(expr_type);

	this->program->Variables->insert({name, var});
	cout << var->name << " = " << assignment->right << endl;
}

// Parse a function definition instruction
void Parser::ins_function_def(d_string * code, string name) {
	cout << "found a function definiton. Name = " << name << endl;
}

// Parse an expression
d_uint Parser::parse_expr(d_string * code, string * expr) {
	static Token * tok;
	string name;

	tok = this->lexer->next_token(code);

	while(tok->type != TOKEN_CODE_END && tok->type != TOKEN_OP_DOT && tok->type != TOKEN_OP_LPAR) {
		*expr += tok->value;

		// If number of var/func name
		if(IS_NUM(tok->type) || tok->type == TOKEN_NAME) {
			tok = this->lexer->next_token(code);

			// Name
			if(tok->type == TOKEN_NAME) {
				name = tok->value;
				tok = this->lexer->next_token(code);

				if(tok->type == TOKEN_OP_RPAR)
					this->ins_function_call(code, name);
				else
					this->check_variable(name);
			}

			if(tok->type == TOKEN_OP_LPAR)
				break;

			if((! IS_ARITH(tok->type)) && tok->type != TOKEN_OP_DOT) {
				std::stringstream err;
				err << "faulty arithmetic operations on line " << this->lexer->line_nr << ":" << this->lexer->character << ".";

				ERROR(new Error(ERRNO_SYNTAX, err.str()));
			}

			*expr += tok->value;
		}

		// If right para, recursive function call
		if(tok->type == TOKEN_OP_RPAR) {
			this->parse_expr(code, expr);

			if(tok->type != TOKEN_OP_LPAR) {
				std::stringstream err;
				err << "missing ')' on line " << this->lexer->line_nr << ":" << this->lexer->character << ".";

				ERROR(new Error(ERRNO_SYNTAX, err.str()));
			}

			*expr += tok->value;
		}

		tok = this->lexer->next_token(code);
	}

	// No ending delimiter
	if(tok->type == TOKEN_CODE_END) {
		std::stringstream err;
		err << "unexpected end of file on line " << this->lexer->line_nr << ":" << this->lexer->character << ".";

		ERROR(new Error(ERRNO_SYNTAX, err.str()));
	}


	return 1;
}

