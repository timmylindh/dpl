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
	this->return_types = new std::map<int, void *>;
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

// Determine whether a function has a certain return type or not
// return 0 if not
int Function::check_return_type(int type) {
	if(return_types->find(type) == return_types->end())
		return 0;

	return 1;
}

// Returns the first return type
int Function::get_return_type() {
	return return_types->begin()->first;
}
