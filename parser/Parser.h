/*
 * DParser.h
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "../dtypes.h"
#include "../lexer/Lexer.h"
#include "Program.h"

class Parser {

	public:
		d_uint parse(d_string code, Program * program);

		Parser(Lexer * lexer);
		virtual ~Parser();

	private:
		Lexer * lexer;

};

#endif /* PARSER_H_ */
