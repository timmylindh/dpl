/*
 * Lexer.h
 *
 *  Created on: 13 nov. 2017
 *      Author: timmy.lindholm
 */

#ifndef LEXER_H_
#define LEXER_H_

#include <iostream>
#include <cctype>
#include <unordered_map>

// Tokens
#define TOK_NULL 0

#define TOK_INT 1
#define TOK_FLOAT 2

#define TOK_STRING 3
#define TOK_NAME 4

#define TOK_PLUS 5
#define TOK_MINUS 6
#define TOK_MULT 7
#define TOK_DIV 8
#define TOK_MOD 9

#define TOK_RIGHT_PAR 10
#define TOK_LEFT_PAR 11
#define TOK_RIGHT_SBRACK 12
#define TOK_LEFT_SBRACK 13
#define TOK_RIGHT_CBRACK 14
#define TOK_LEFT_CBRACK 15
#define TOK_PIPE 16

#define TOK_UNI_QUANT 17
#define TOK_MEMBER_OF 18
#define TOK_WHILE 19
#define TOK_PLACE 1000
#define TOK_IMPLIES 20

#define TOK_GREATER 21
#define TOK_LESSER 22
#define TOK_GREATER_EQUAL 23
#define TOK_LESSER_EQUAL 24
#define TOK_EQUAL 25
#define TOK_EQUAL_EQUAL 26

#define TOK_IF 27
#define TOK_ELSE_IF 28

#define TOK_DOT 29
#define TOK_COLON 30
#define TOK_COMMA 31

#define TOK_AT 33

// Whether token is of assignment type
#define IS_ASSIGNMENT(type) (type == TOK_EQUAL)

// Whether token is of operator type
#define IS_OPERATOR(type) (type == TOK_PLUS || type == TOK_MINUS || type == TOK_MULT || type == TOK_DIV)

// Defines a single token
class Token {

public:

	const char * value;
	int type;

	// Initialize a new token
	Token(std::string * value, int type) {
		this->value = value->c_str();
		this->type = type;
	}

	Token(char * value, int type) {
		this->value = value;
		this->type = type;
	}

};

class Lexer {

public:
	Lexer();

	// Number of lines parsed
	int n_lines;

	// A reference to the last token
	Token * last_token;

	// Return the next token in char buffer
	Token * next_token();

	// Sets the internal buffer to the code pointed to by argument
	void set_input_code(char * buffer);

private:
	char * buffer;
	char * pt;

	// A list of tokens and their corresponding token ids
	std::unordered_map<std::string, int> symbols;
	std::unordered_map<std::string, int> keywords;

	// Used to parse a string for an integer or a float
	std::string * get_number(int &type);

	// Get a string
	std::string * get_string(char delimiter, int &type);

	// Get a reserved keyword or variable name
	std::string * get_keyword(int &type);

	// Get a symbol, for instance a + or a - sign
	std::string * get_symbol(int &type);
};

#endif /* LEXER_H_ */
