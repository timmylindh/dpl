/*
 * Token.cpp
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

#include "Token.h"

// Define a token with value and type
Token::Token(d_string value, d_uint type) {
	this->value = value;
	this->type = type;
}

Token::~Token() {

}

// Fetch all reserved keywords
void Token::get_keywords(map<const d_string, d_uint> * KEYWORDS) {
	(*KEYWORDS) = {
			{(const d_string) "if", TOKEN_IF}
	};
}
