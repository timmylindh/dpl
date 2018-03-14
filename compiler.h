/*
 * Compiler.h
 *
 *  Created on: 13 nov. 2017
 *      Author: timmy.lindholm
 */

#ifndef COMPILER_H_
#define COMPILER_H_

#include "parser.h"
#include "mem/program.h"
#include "translator.h"

class Compiler {

public:
	Compiler();
	virtual ~Compiler();

	// Called to compile a source dpl file
	int compile(char * file_name);

	// Line start
	int line_start = 0;

private:
	Parser * parser;
	Translator * translator;
	char * buffer;

	// Main program
	Program * program;

	// Open a file and put the contents in a buffer, might throw an error
	char * read_file(char * file_name);


};

#endif /* COMPILER_H_ */
