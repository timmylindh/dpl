/*
 * DLexer.h
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

#ifndef LEXER_H_
#define LEXER_H_

#include <map>
#include <iostream>

#include "../dtypes.h"
#include "../Token.h"

using std::map;

class Lexer {

	public:
		d_uint line_nr;
		d_uint character;

		virtual Token * next_token(d_string * code);

		Lexer();
		virtual ~Lexer();

	private:
		map<const std::string, d_uint> * KEYWORDS;
		map<const std::string, d_uint> * OPERATORS;

		const std::string get_number(d_string * code, d_uint * type);
		const std::string get_string(d_string * code);
		const d_uint get_keyword_name(d_string * code, std::string * value);
		const d_uint get_operator(d_string * code, std::string * value);
};

#endif /* LEXER_H_ */
