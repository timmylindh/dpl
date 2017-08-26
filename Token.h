/*
 * Token.h
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

#ifndef TOKEN_H_
#define TOKEN_H_

#include <map>
#include <iostream>
#include "dtypes.h"

using std::map;

// Token types
#define TOKEN_STRING 1
#define TOKEN_CODE_END 2
#define TOKEN_INT 3
#define TOKEN_FLOAT 4
#define TOKEN_NAME 5

// Token operators
#define TOKEN_OP_PLUS 6
#define TOKEN_OP_MINUS 7
#define TOKEN_OP_MULT 8
#define TOKEN_OP_DIV 9
#define TOKEN_OP_IF 10
#define TOKEN_OP_UNI 11
#define TOKEN_OP_ELEMOF 12
#define TOKEN_OP_ASSIGN 13
#define TOKEN_OP_RPAR 14
#define TOKEN_OP_LPAR 15
#define TOKEN_OP_RBRACK 16
#define TOKEN_OP_LBRACK 17
#define TOKEN_OP_EQUALS 18
#define TOKEN_OP_DO 19
#define TOKEN_OP_DOT 20
#define TOKEN_OP_RCURL 21
#define TOKEN_OP_LCURL 22
#define TOKEN_OP_COMMA 23
#define TOKEN_OP_COLON 24

// Keyword tokens

class Token {

	public:
		std::string value;
		d_uint type;

		static void get_keywords(map<const std::string, d_uint> * KEYWORDS);
		static void get_operators(map<const std::string, d_uint> * OPERATORS);

		Token(std::string value, d_uint type);
		virtual ~Token();
};

#endif /* TOKEN_H_ */
