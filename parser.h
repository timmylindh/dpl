/*
 * Parser.h
 *
 *  Created on: 13 nov. 2017
 *      Author: timmy.lindholm
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "lexer.h"

class Parser {

public:
	Parser();

	// Parse the code which resides in buffer
	void parse(char * buffer);
	void parse();

	// Sets the internal buffer to the code pointed to by the argument
	void set_input_code(char * buffer);

private:
	Lexer * lexer;
	char * buffer;
};

#endif /* PARSER_H_ */
