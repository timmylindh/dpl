/*
 * DLexer.cpp
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

#include <cctype>
#include <iostream>

#include "Lexer.h"
#include "../Token.h"

Lexer::Lexer() {
	// Get all reserved keywords
	this->KEYWORDS = new map<const d_string, d_uint>;
	Token::get_keywords(this->KEYWORDS);
}

Lexer::~Lexer() {
	// TODO Auto-generated destructor stub
}

// Get the next token in code
Token Lexer::next_token(d_string * code) {
	d_string value;
	d_uint type;

	// Skip spaces and whitespace
	while(isspace(**code))
		(*code)++;

	// Check if end of code
	if(**code == '\0')
		return Token(NULL, TOKEN_CODE_END);

	// Check if integer or number
	if(isdigit(**code)) {
		value = Lexer::get_number(code, &type);
		return Token(value, type);
	}

	// Check if string
	if(**code == '"') {
		value = Lexer::get_string(code);
	}


}

// Get an integer or floating point number
const d_string Lexer::get_number(d_string * code, d_uint * type) {
	std::string value;
	*type = TOKEN_INT;

	// Fetch the integer or floating point number
	while(isdigit(**code) || **code == '.') {
		if(**code == '.')
			*type = TOKEN_FLOAT;

		value += *((*code)++);
	}

	return (d_string) value.c_str();
}

// Get a string
const d_string Lexer::get_string(d_string * code) {
	std::string value;

	// Fetch the string
	while(**code != '"' && **code != '\0')
		value += *((*code)++);

	// No ending string delimiter
	if(**code == '\0') {

	}

	return (d_string) value.c_str();
}
