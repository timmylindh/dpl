/*
 * function.h
 *
 *  Created on: 17 nov. 2017
 *      Author: eatit
 */

#ifndef MEM_FUNCTION_H_
#define MEM_FUNCTION_H_

#include <vector>
#include <map>
#include "variable.h"
#include "program.h"

class Function : public Program {

public:
	Function(Program * parent_program);

	// The name of the function
	char * name;

	// Get the next argument in argument vector
	// return 0 if last
	Argument * get_next_argument();

	// Check if the function has a certain return type
	// return 0 if not
	int check_return_type(int type);

	// Returns the first return type
	int get_return_type();

private:
	// The arguments that the function takes
	std::vector<Argument *> * arguments;

	// The possible return types of the function
	std::map<int, void *> * return_types;

	// Arguments index
	int args_index;
};

#endif /* MEM_FUNCTION_H_ */
