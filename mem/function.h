/*
 * function.h
 *
 *  Created on: 17 nov. 2017
 *      Author: eatit
 */

#ifndef MEM_FUNCTION_H_
#define MEM_FUNCTION_H_

#include <vector>

#include "variable.h"
#include "program.h"

class Function : public Program {

public:
	Function(Program * parent_program);

	// The name of the function
	char * name;

	// The arguments that the function takes
	std::vector<Argument *> * arguments;
};

#endif /* MEM_FUNCTION_H_ */
