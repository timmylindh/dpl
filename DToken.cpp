/*
 * DToken.cpp
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

#include "DToken.h"

// Define a token with value and type
D_Token::D_Token(d_string value, d_uint type) {
	this->value = value;
	this->type = type;
}

D_Token::~D_Token() {

}

