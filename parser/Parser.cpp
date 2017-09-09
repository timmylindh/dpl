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

Parser::Parser(Lexer * lexer, Program * global_program) {
	this->lexer = lexer;
	this->program = global_program;
	this->global_program = global_program;
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
		else
			ERROR(new Error(ERRNO_SYNTAX, "incorrect syntax"));


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

	// Check whether variable already exists
	if(! (var = this->fetch_variable(name))) {
		var = new Variable(name);
		this->program->Variables->insert({name, var});
	}

	var->Types->push_back(expr_type);
	var->History->push_back(expr_type);

	cout << var->name << " = " << assignment->right << endl;
}

// Parse a function definition instruction
void Parser::ins_function_def(d_string * code, string name) {
	cout << "found a function definiton. Name = " << name << endl;
}

// Parse an expression,return the data type of the expression
d_uint Parser::parse_expr(d_string * code, string * expr) {
	static Token * tok;
	d_uint type;

	// Accepted variable types for expression
	std::vector<d_uint> var_types = {TOKEN_FLOAT, TOKEN_INT};
	type = TOKEN_INT;

	tok = this->lexer->next_token(code);

	// String parsing
	if(tok->type == TOKEN_STRING) {
		//this->parse_string_expr();
	}

	else
	// Numeric parsing
	while(tok->type != TOKEN_CODE_END && tok->type != TOKEN_OP_DOT && tok->type != TOKEN_OP_LPAR) {
		*expr += tok->value;

		// If number of var/func name
		if(IS_NUM(tok->type) || tok->type == TOKEN_NAME) {
			// Name
			if(tok->type == TOKEN_NAME)
				tok = this->parse_token_name(code, tok, &type, var_types);
			else
				tok = this->lexer->next_token(code);

			// Check next token
			if(tok->type == TOKEN_OP_LPAR)
				break;

			else if(tok->type == TOKEN_OP_DOT)
				continue;

			else if (! IS_ARITH(tok->type)) {
				std::stringstream err;
				err << "faulty arithmetic operation on line " << this->lexer->line_nr << ":" << this->lexer->character << ".";

				ERROR(new Error(ERRNO_SYNTAX, err.str()));
			}

			*expr += tok->value;
		}

		// If right para, recursive function call
		else if(tok->type == TOKEN_OP_RPAR) {
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

	return type;
}

// Function call instruction, return return type
d_uint Parser::ins_function_call(d_string * code, string name) {
	Function * func;
	I_Function_Call * instruction;
	std::vector<string> * args;
	Token * tok;

	// Fetch function
	if(! (func = this->fetch_function(name))) {
		std::stringstream err;
		err << "undefined function " << name << " on line " << this->lexer->line_nr << ":" << this->lexer->character << ".";

		ERROR(new Error(ERRNO_UNDEF, err.str()));
	}

	// Get function arguments
	args = new std::vector<string>();

	this->get_function_args(code, args);

	// Add function call instruction
	instruction = new I_Function_Call(this->program, INSTRUCTION_FUNC_CALL);

	instruction->Arguments = args;
	instruction->name = name;

	return func->Return_types->back();
}

// Parse and get function argument
string Parser::get_function_args(d_string * code, std::vector<string> * args) {

}

// Fetch a function from the current or global program tree
Function * Parser::fetch_function(string name) {
	std::map<std::string, Function *>::iterator it;

	// Check in current tree
	if((it = this->program->Functions->find(name)) != this->program->Functions->end())
		return it->second;

	if((it = this->global_program->Functions->find(name)) != this->global_program->Functions->end())
		return it->second;

	return 0;
}

// Fetch a variable from the current or global program tree
Variable * Parser::fetch_variable(string name) {
	std::map<std::string, Variable *>::iterator it;

	// Check if variable exists in current tree
	if((it = this->program->Variables->find(name)) != this->program->Variables->end())
		return it->second;

	// Check global tree
	if((it = this->global_program->Variables->find(name)) != this->global_program->Variables->end())
		return it->second;

	// No such variable
	return 0;
}

// Parse a NAME token and return the type of func (return) or var
Token * Parser::parse_token_name(d_string * code, Token * tok, d_uint * type, std::vector<d_uint> allowed_types) {
	std::vector<d_uint>::iterator it;
	Variable * var;
	string name;

	name = tok->value;
	tok = this->lexer->next_token(code);

	// Function call
	if(tok->type == TOKEN_OP_RPAR) {
		this->ins_function_call(code, name);

		return 0;
	}

	// Variable
	if(! (var = this->fetch_variable(name))) {
		std::stringstream err;
		err << "undefined variable " << name << " on line " << this->lexer->line_nr << ":" << this->lexer->character << ".";

		ERROR(new Error(ERRNO_UNDEF, err.str()));
	}

	// Validate the variable types
	if(! (*type = this->validate_type(allowed_types, var->History->back()))) {
		std::stringstream err;
		err << name << " is of a invalid type on line " << this->lexer->line_nr << ":" << this->lexer->character << ".";

		ERROR(new Error(ERRNO_TYPE, err.str()));
	}

	return tok;
}

// Validate function/variable type
d_uint Parser::validate_type(std::vector<d_uint> types, d_uint type) {
	std::vector<d_uint>::iterator it;
	d_uint final_type = 0;

	for(it = types.begin(); it != types.end(); it++)
	if(*it == type) {
		final_type = type;
		break;
	}

	// O if invalid type
	return final_type;
}
