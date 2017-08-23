/*
 * DLexer.h
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

#ifndef LEXER_H_
#define LEXER_H_

#include <map>

#include "../dtypes.h"
#include "../Token.h"

using std::map;

class Lexer {

	public:
		Lexer();
		virtual ~Lexer();

	private:
		map<const d_string, d_uint> * KEYWORDS;

		Token next_token(d_string * code);
		const d_string get_number(d_string * code, d_uint * type);
		const d_string get_string(d_string * code);
};

#endif /* LEXER_H_ */
