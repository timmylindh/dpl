/*
 * Lexer.cpp
 *
 *  Created on: 13 nov. 2017
 *      Author: timmy.lindholm
 */

#include <iostream>
#include <cctype>

#include "lexer.h"

Lexer::Lexer() {

	buffer = NULL;
	pt = NULL;
	last_token = NULL;
}

// Returns the next token in input buffer
Token * Lexer::next_token() {
	char * pt;

	pt = this->pt;

	// Integer or float
	if(isdigit(*pt));
}

/*
 * Sets the internal code buffer to the string pointed to by
 * [buffer].
 */
void Lexer::set_input_code(char * buffer) {
	this->buffer = buffer;
	this->pt = this->buffer;
}

