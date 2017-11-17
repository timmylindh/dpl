/*
 * Lexer.h
 *
 *  Created on: 13 nov. 2017
 *      Author: timmy.lindholm
 */

#ifndef LEXER_H_
#define LEXER_H_

// Defines a single token
struct Token {

	char * value;
	int type;

};

class Lexer {

public:
	Lexer();

	// Return the next token in char buffer
	Token * next_token();

	// Sets the internal buffer to the code pointed to by argument
	void set_input_code(char * buffer);

private:
	char * buffer;
};

#endif /* LEXER_H_ */
