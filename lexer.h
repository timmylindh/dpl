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
	virtual ~Lexer();

	// Return the next token in char buffer
	Token * next_token();
};

#endif /* LEXER_H_ */
