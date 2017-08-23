/*
 * Token.h
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

#ifndef TOKEN_H_
#define TOKEN_H_

#include <map>
#include "dtypes.h"

using std::map;

// Token types
#define TOKEN_STRING 1
#define TOKEN_CODE_END 2
#define TOKEN_INT 3
#define TOKEN_FLOAT 4

// Keyword tokens
#define TOKEN_IF 5

class Token {

	public:
		d_string value;
		d_uint type;

		static void get_keywords(map<const d_string, d_uint> * KEYWORDS);

		Token(const d_string value, d_uint type);
		virtual ~Token();
};

#endif /* TOKEN_H_ */
