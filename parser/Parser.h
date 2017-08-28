/*
 * DParser.h
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include "../dtypes.h"
#include "../lexer/Lexer.h"
#include "Program.h"

using std::string;
using std::cout;
using std::endl;

class Parser {

	public:
		virtual d_uint parse(d_string * code, Program * program);

		Parser(Lexer * lexer);
		virtual ~Parser();

	private:
		Lexer * lexer;
		Program * program;

		void ins_assignment(d_string * code, string name, d_uint type); // Assignment instruction
		void ins_function_def(d_string * code, string name); // Function definiton instruction
};

#endif /* PARSER_H_ */
