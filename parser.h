/*
 * Parser.h
 *
 *  Created on: 13 nov. 2017
 *      Author: timmy.lindholm
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "lexer.h"
#include "mem/program.h"

class Parser {

public:
	Parser();

	// Parse the code which resides in buffer, use the program passed
	// as argument
	void parse(Program * program);

	// Entry point, call this function to set up a new program and
	// to initialize a new parser
	Program * parse();

	// Sets the internal buffer to the code pointed to by the argument
	void set_input_code(char * buffer);

private:
	Lexer * lexer;
	char * buffer;

	// Global program
	Program * global_program;

	// Parse an assignment operation, for instace = or +=
	void parse_assignment_operation(char * name, int assign_type);

};

#endif /* PARSER_H_ */
