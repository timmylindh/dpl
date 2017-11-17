/*
 * variable.h
 *
 *  Created on: 17 nov. 2017
 *      Author: eatit
 */

#ifndef MEM_VARIABLE_H_
#define MEM_VARIABLE_H_

#include <iostream>

class Variable {

public:
	Variable(char * name, char * value, int type);

	// The name of the variable
	char * name;

	// The value of the variable
	void * value;

	// The type of the variable
	int type;

};

// Defines a function argument
class Argument : public Variable {

public:
	Argument(char * name, char * value, int type);

	// Default value for argument
	char * default_value;

	// Default type for argument
	int default_type;

};


// Defines a function return value
class ReturnValue : public Variable {

};

#endif /* MEM_VARIABLE_H_ */
