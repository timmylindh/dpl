/*
 * DLexer.cpp
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

#include <cctype>
#include <iostream>
#include <sstream>

#include "Lexer.h"
#include "../Token.h"
#include "../error/Error.h"

Lexer::Lexer() {
	// Get all reserved keywords
	this->KEYWORDS = new map<const std::string, d_uint>;
	this->OPERATORS = new map<const std::string, d_uint>;

	Token::get_keywords(this->KEYWORDS);
	Token::get_operators(this->OPERATORS);

	this->line_nr = 1;
	this->character = 0;
}

Lexer::~Lexer() {
	// TODO Auto-generated destructor stub
}

// Get the next token in code
Token * Lexer::next_token(d_string * code) {
	std::string value;
	d_uint type;

	// Skip spaces and whitespace
	while(isspace(**code)) {
		if(**code == '\n')
			this->line_nr++;

		this->character++;

		(*code)++;
	}

	// Check if end of code
	if(**code == '\0')
		return new Token("", TOKEN_CODE_END);

	// Check if integer or float number
	if(isdigit(**code)) {
		value = Lexer::get_number(code, &type);
		return new Token(value, type);
	}

	// Check if string
	if(**code == '"') {
		value = Lexer::get_string(code);
		return new Token(value, TOKEN_STRING);
	}

	// Get operator
	if((type = this->get_operator(code, &value)))
		return new Token(value, type);

	// Check if keyword or name
	if((type = this->get_keyword_name(code, &value)))
		return new Token(value, type);

	// Error, not recognized
	{
		std::stringstream err;
		err << "unexpected '" << **code << "', on line " << this->line_nr << ":" << this->character << ".";

		ERROR(new Error(ERRNO_UNK, err.str()));
	}

	return new Token(0, 0);
}

// Get an integer or floating point number
const std::string Lexer::get_number(d_string * code, d_uint * type) {
	std::string value;
	*type = TOKEN_INT;

	// Fetch the integer or floating point number
	while(isdigit(**code) || **code == '.') {
		if(**code == '.')
			*type = TOKEN_FLOAT;

		value += *((*code)++);
	}

	return value;
}

// Get a string
const std::string Lexer::get_string(d_string * code) {
	std::string value;

	(*code)++;

	// Fetch the string
	while(**code != '"' && **code != '\0')
		value += *((*code)++);

	// No ending string delimiter
	if(**code == '\0') {
		std::stringstream err;
		err << "unexpected end of string, missing '\"' on line " << this->line_nr << ":" << this->character << ".";

		ERROR(new Error(ERRNO_STR_DELIM, err.str()));
	}

	(*code)++;

	return value;
}

// Get operator
const d_uint Lexer::get_operator(d_string * code, std::string * value) {
	d_string start;
	std::string  tmp, val;
	std::map<std::string, d_uint>::iterator it;
	d_uint type;

	start = *code;
	tmp += **code;

	// Fetch the whole operator, >= for instance
	while((it = OPERATORS->find(tmp)) != OPERATORS->end()) {
		val += *((*code)++);
		tmp += **code;

		type = it->second;
	}

	// No matching operator
	if(val.empty()) {
		*code = start;
		return 0;
	}

	*value = val;
	return type;

}

// Get keyword or var/func name, return type
const d_uint Lexer::get_keyword_name(d_string * code, std::string * value) {
	std::string val;
	std::map<std::string, d_uint>::iterator it;

	// Fetch the word
	while(isalnum(**code) || **code == '_')
		val += *((*code)++);

	*value = val;

	// Check whether word is a keyword
	if((it = KEYWORDS->find(val)) != KEYWORDS->end())
		return it->second;

	if(val.empty())
		return 0;

	// Function or variable
	return TOKEN_NAME;
}

