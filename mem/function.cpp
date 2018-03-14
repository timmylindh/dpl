/*
 * function.cpp
 *
 *  Created on: 17 nov. 2017
 *      Author: eatit
 */

#include "function.h"

Function::Function(Program * parent_program) : Program(parent_program, PROGRAM_FUNCTION) {

	this->name = NULL;
	this->arguments = new std::vector<Argument *>;
	this->args_index = 0;
	this->return_type = 0;
}

// Get the next argument in argument vector, return 0 if last one
// and reset index
Argument * Function::get_next_argument() {
	Argument * arg;

	arg = arguments->at(args_index++);

	if(args_index == arguments->size())
		args_index = 0;

	return arg;
}

// Return the size of arguments
int Function::get_arguments_size() {
	return arguments->size();
}

// Get the variable [name] in current program
// return 0 if it does not exist
Variable * Function::get_variable(std::string name) {
	std::unordered_map<std::string, Variable *>::iterator it;

	// Search arguments
	for(auto arg : *arguments) {
		if(! strcmp(arg->name, name.c_str())) {
			std::cerr << "arg type: " << arg->type << std::endl;
			return arg;
		}
	}

	// Search local scope
	if((it = variables->find(name)) != variables->end())
		return it->second;

	// Search global scope
	Program * scope;
	scope = this;

	while(scope != NULL && scope->program_type != PROGRAM_GLOBAL)
		scope = scope->parent_program;

	if((it = scope->variables->find(name)) != scope->variables->end())
		return it->second;

	return 0;
}

// Push an argument to the arguments vector
void Function::push_argument(Argument * argument) {
	arguments->push_back(argument);
}

// Determine whether a function has a certain return type or not
// return 0 if not
int Function::check_return_type(int type) {
	if(return_type == type)
		return 0;

	return 1;
}

// Returns the first return type
int Function::get_return_type() {
	return return_type;
}

// Set the return type
void Function::set_return_type(int type) {
	return_type = type;
}
