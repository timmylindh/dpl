/*
 * Lexer.cpp
 *
 *  Created on: 13 nov. 2017
 *      Author: timmy.lindholm
 */

#include <iostream>

#include "lexer.h"

Lexer::Lexer() {

	buffer = NULL;

}

/*
 * Sets the internal code buffer to the string pointed to by
 * [buffer].
 */
void Lexer::set_input_code(char * buffer) {
	this->buffer = buffer;
}

