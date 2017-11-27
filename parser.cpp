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

}

/*
 * Parses the code which resides in buffer
 * May be called recursively, thus the non-static buffer
 * Pointer.
*/
void Parser::parse(char * buffer) {
	Token * tok;

	std::cout << "OUTPUT:" << std::endl;

	while((tok = this->lexer->next_token())->type != TOK_NULL)
		std::cout << tok->type << " : " << tok->value << std::endl;
}

// Calls the parse function with the internal buffer as argument
void Parser::parse() {
	this->parse(this->buffer);
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
