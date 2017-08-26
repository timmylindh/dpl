/*
 * DParser.cpp
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

#include <iostream>
#include "Parser.h"

Parser::Parser(Lexer * lexer) {
	this->lexer = lexer;
}

Parser::~Parser() {

}

// Parse a single, or a set of instructions
d_uint Parser::parse(d_string code, Program * program) {
	Token * tok;

	while((tok = this->lexer->next_token(&code))->type != TOKEN_CODE_END)
		std::cout << tok->value << " | " << tok->type << std::endl;

	return 0;
}
