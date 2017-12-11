/*
 * Lexer.cpp
 *
 *  Created on: 13 nov. 2017
 *      Author: timmy.lindholm
 */

#include "lexer.h"
#include "error.h"

Lexer::Lexer() {

	n_lines = 1;
	buffer = NULL;
	pt = NULL;
	last_token = NULL;

	// Initialize symbols map
	symbols["+"] = TOK_PLUS;
	symbols["-"] = TOK_MINUS;
	symbols["*"] = TOK_MULT;
	symbols["/"] = TOK_DIV;
	symbols["%"] = TOK_MOD;

	symbols[")"] = TOK_RIGHT_PAR;
	symbols["("] = TOK_LEFT_PAR;
	symbols["]"] = TOK_RIGHT_SBRACK;
	symbols["["] = TOK_LEFT_SBRACK;
	symbols["}"] = TOK_RIGHT_CBRACK;
	symbols["{"] = TOK_LEFT_CBRACK;
	symbols["|"] = TOK_PIPE;

	symbols["V"] = TOK_UNI_QUANT;
	symbols["E"] = TOK_MEMBER_OF;
	symbols["£"] = TOK_WHILE;
	symbols["--"] = TOK_PLACE;
	symbols["-->"] = TOK_IMPLIES;

	symbols[">"] = TOK_GREATER;
	symbols["<"] = TOK_LESSER;
	symbols[">="] = TOK_GREATER_EQUAL;
	symbols["<="] = TOK_LESSER_EQUAL;
	symbols["="] = TOK_EQUAL;
	symbols["=="] = TOK_EQUAL_EQUAL;

	symbols["?"] = TOK_IF;
	symbols["|?"] = TOK_ELSE_IF;

	symbols["."] = TOK_DOT;
	symbols[":"] = TOK_COLON;
	symbols[","] = TOK_COMMA;

	symbols["&"] = TOK_PLACE;
	symbols["&&"] = TOK_AND;
	symbols["||"] = TOK_OR;

	// Initialize keywords map
	keywords["ret"] = TOK_RETURN;
}

// Returns the next token in input buffer
Token * Lexer::next_token() {
	int type;
	std::string * value;

	type = TOK_NULL;

	// End of code
	if(*pt == '\0') {
		value = new std::string;
		return new Token(value, type);
	}

	// Skip spaces
	while(isspace(*pt)) {
		if(*pt == '\n')
			n_lines++;

		pt++;
	}

	// Integer or float
	if(isdigit(*pt))
		value = get_number(type);

	// String
	else if(*pt == '"' || *pt == '\'')
		value = get_string(*pt++, type);

	// Keyword
	else if(isalpha(*pt))
		value = get_keyword(type);

	// Symbol
	else
		value = get_symbol(type);

	last_token = new Token(value, type);
	return last_token;
}

// Fetch an integer or a float, return the corresponding string
// and set type to the TOK_TYPE accordingly
std::string * Lexer::get_number(int &type) {
	std::string * value;

	value = new std::string;
	type = TOK_INT;

	while(isdigit(*pt) || *pt == '.') {
		if(*pt == '.') {
			if(type == TOK_FLOAT || (! isdigit(*(pt + 1))))
				break;

			type = TOK_FLOAT;
		}

		*value += *pt++;
	}

	return value;
}

// Fetch a string using the delimiter specified, either " or '
std::string * Lexer::get_string(char delimiter, int &type) {
	std::string * value;
	value = new std::string;

	// Loop until ending delimiter
	while(*pt != delimiter && *pt != '\0')
		*value += *pt++;

	// No ending delimiter
	if(*pt == '\0')
		ERROR(T_CRIT, "no ending delimiter %c for string, on line %d.", delimiter, n_lines);

	pt++;
	type = TOK_STRING;

	return value;
}

/* Fetches a keyword or variable name, based on whether the name is a reserved
 * keyword or not.
 */
std::string * Lexer::get_keyword(int &type) {
	std::string * search;
	std::unordered_map<std::string, int>::iterator it;

	search = new std::string;

	// Get name
	while(isalnum(*pt) || *pt == '_')
		*search += *pt++;

	// Keyword or name
	if((it = keywords.find(*search)) == symbols.end())
		type = TOK_NAME;
	else
		type = it->second;

	return search;
}

// Fetches a symbol based on whether it is in the symbols map or not
std::string * Lexer::get_symbol(int &type) {
	std::string search;
	std::unordered_map<std::string, int>::iterator it, _it;

	search = *pt;
	type = TOK_NULL;

	// Check for symbol match
	while((_it = symbols.find(search)) != symbols.end()) {
		it = _it;
		type = it->second;

		search += *(++pt);
	}

	// No match
	if(type == TOK_NULL)
		ERROR(T_CRIT, "unknown symbol %s, on line %d.", search.c_str(), n_lines);

	return new std::string(it->first);
}

/*
 * Sets the internal code buffer to the string pointed to by
 * [buffer].
 */
void Lexer::set_input_code(char * buffer) {
	this->buffer = buffer;
	this->pt = this->buffer;
}

