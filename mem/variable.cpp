/*
 * variable.cpp
 *
 *  Created on: 17 nov. 2017
 *      Author: eatit
 */

#include "variable.h"

// Initialize a new variable
Variable::Variable(const char * name, std::vector<Token *> * value, int type) {

	this->name = name;
	this->value = value;
	this->type = type;

}

// Initialize a new argument
Argument::Argument(char * name, std::vector<Token *> * value, int type)
: Variable(name, value, type) {

	this->default_value = NULL;
	this->default_type = 0;

}
