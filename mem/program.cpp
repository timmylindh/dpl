/*
 * program.cpp
 *
 *  Created on: 17 nov. 2017
 *      Author: eatit
 */

#include "program.h"

// Initialize a new program
Program::Program(Program * parent_program) {
	this->parent_program = parent_program;

	this->variables = new std::unordered_map<std::string, Variable *>();
	this->instructions = new std::queue<Instruction *>();
}

// Initialize a new global program
GlobalProgram::GlobalProgram() : Program(NULL) {
	this->functions = new std::unordered_map<std::string, Function *>();
}

