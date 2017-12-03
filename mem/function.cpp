/*
 * function.cpp
 *
 *  Created on: 17 nov. 2017
 *      Author: eatit
 */

#include "function.h"

Function::Function(Program * parent_program) : Program(parent_program) {

	this->name = NULL;
	this->arguments = new std::vector<Argument *>;
	this->return_types = new std::vector<int>;
	this->args_index = 0;
}

// Get the next argument i argument vector, return 0 if last one
// and reset index
Argument * Function::get_next_argument() {
	if(args_index == arguments->size()) {
		args_index = 0;
		return 0;
	}

	return arguments->at(args_index++);
}
