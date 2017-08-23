/*
 * DToken.h
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

#ifndef DTOKEN_H_
#define DTOKEN_H_

#include "dtypes.h"

// Token type
#define TOKEN_STRING 1

class D_Token {

	public:
		d_string value;
		d_uint type;

	D_Token(d_string value, d_uint type);
	virtual ~D_Token();
};

#endif /* DTOKEN_H_ */
