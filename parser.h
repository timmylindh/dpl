/*
 * Parser.h
 *
 *  Created on: 13 nov. 2017
 *      Author: timmy.lindholm
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "lexer.h"

class Parser {

public:
	Parser();
	virtual ~Parser();


private:
	Lexer * lexer;
};

#endif /* PARSER_H_ */
