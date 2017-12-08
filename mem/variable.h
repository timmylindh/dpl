/*
 * variable.h
 *
 *  Created on: 17 nov. 2017
 *      Author: eatit
 */

#ifndef MEM_VARIABLE_H_
#define MEM_VARIABLE_H_

#include <iostream>
#include <vector>

#include "../lexer.h"

class Variable {

public:
	Variable(const char * name, std::vector<Token *> * value, int type);

	// The name of the variable
	const char * name;

	// The value of the variable
	std::vector<Token *> * value;

	// The type of the variable
	int type;

};

// Defines a function argument
class Argument : public Variable {

public:
	Argument(const char * name, std::vector<Token *> * value, int type);

	// Default value for argument
	std::vector<Token *> * default_value;

	// Default type for argument
	int default_type;

};


// Defines a function return value
class ReturnValue : public Variable {

};

#endif /* MEM_VARIABLE_H_ */
