/*
 * Parser.cpp
 *
 *  Created on: 13 nov. 2017
 *      Author: timmy.lindholm
 */

#include <iostream>

#include "parser.h"
#include "lexer.h"

Parser::Parser() {

	this->lexer = new Lexer;
	this->buffer = NULL;
	this->global_program = NULL;

}

/*
 * Parses the code which resides in buffer
 * May be called recursively, thus the non-static program
 * pointer
*/
void Parser::parse(Program * program) {
	Token * tok;

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
void parse_assignment_operation(char * name, int assign_type) {

}

// Calls the main parse function with the global program as argument
Program * Parser::parse() {
	global_program = new Program(NULL);

	this->parse(global_program);

	return global_program;
}

/*
 * Sets the internal code buffer to the argument
 * This way we do not have to pass the buffer to the lexer
 * Each parse() call.
 */
void Parser::set_input_code(char * buffer) {
	this->buffer = buffer;
	this->lexer->set_input_code(buffer);
}
