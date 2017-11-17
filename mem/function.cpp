/*
 * function.cpp
 *
 *  Created on: 17 nov. 2017
 *      Author: eatit
 */

#include "function.h"

Function::Function(Program * parent_program) : Program(parent_program) {

	this->name = NULL;
	this->arguments = new std::vector<Argument *>();

}

