/*
 * DParser.cpp
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

#include "Parser.h"

Parser::Parser(Lexer * lexer) {
	this->lexer = lexer;
}

Parser::~Parser() {

}

// Parse a single, or a set of instructions
d_uint Parser::parse(d_string code) {
	return 0;
}

// Get the current program tree
Program * Parser::get_program() {
	return this->program;
}
