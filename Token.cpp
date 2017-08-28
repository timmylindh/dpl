/*
 * Token.cpp
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

#include "Token.h"

// Define a token with value and type
Token::Token(std::string value, d_uint type) {
	this->value = value;
	this->type = type;
}

Token::~Token() {

}

// Fetch all reserved keywords
void Token::get_keywords(map<const std::string, d_uint> * KEYWORDS) {
	(*KEYWORDS) = {
			{(const d_string) "ret", TOKEN_KEY_RETURN}
	};
}

// Fetch all reserved operators
void Token::get_operators(map<const std::string, d_uint> * OPERATORS) {
	(*OPERATORS) = {
			{(const d_string) "+", TOKEN_OP_PLUS},
			{(const d_string) "-", TOKEN_OP_MINUS},
			{(const d_string) "*", TOKEN_OP_MULT},
			{(const d_string) "/", TOKEN_OP_DIV},
			{(const d_string) "=", TOKEN_OP_ASSIGN},
			{(const d_string) "?", TOKEN_OP_IF},
			{(const d_string) "V", TOKEN_OP_UNI},
			{(const d_string) "E", TOKEN_OP_ELEMOF},
			{(const d_string) "(", TOKEN_OP_RPAR},
			{(const d_string) ")", TOKEN_OP_LPAR},
			{(const d_string) "[", TOKEN_OP_RBRACK},
			{(const d_string) "]", TOKEN_OP_LBRACK},
			{(const d_string) "==", TOKEN_OP_EQUALS},
			{(const d_string) "->", TOKEN_OP_EQUALS},
			{(const d_string) ".", TOKEN_OP_DOT},
			{(const d_string) "{", TOKEN_OP_RCURL},
			{(const d_string) "}", TOKEN_OP_LCURL},
			{(const d_string) ",", TOKEN_OP_COMMA},
			{(const d_string) ":", TOKEN_OP_COLON},
			{(const d_string) "*=", TOKEN_OP_MULTASSIGN},
			{(const d_string) "/=", TOKEN_OP_DIVASSIGN},
			{(const d_string) "-=", TOKEN_OP_MINUSASSIGN},
			{(const d_string) "+=", TOKEN_OP_PLUSASSIGN}
	};
}
