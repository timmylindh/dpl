/*
 * Lexer.h
 *
 *  Created on: 13 nov. 2017
 *      Author: timmy.lindholm
 */

#ifndef LEXER_H_
#define LEXER_H_

// Tokens
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
#define TOK_IMPLIES 20

#define TOK_GREATER 21
#define TOK_LESSER 22

#define TOK_IF 23
#define TOK_ELSE_IF 24

// Defines a single token
struct Token {

	char * value;
	int type;

};

class Lexer {

public:
	Lexer();

	// A reference to the last token
	Token * last_token;

	// Return the next token in char buffer
	Token * next_token();

	// Sets the internal buffer to the code pointed to by argument
	void set_input_code(char * buffer);

private:
	char * buffer;
	char * pt;

};

#endif /* LEXER_H_ */
