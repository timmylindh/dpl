/*
 * DParser.cpp
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

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
}

// Parse a function definition instruction
void Parser::ins_function_def(d_string * code, string name) {
	cout << "found a function definiton. Name = " << name << endl;
}

