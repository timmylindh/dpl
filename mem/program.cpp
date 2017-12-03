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

// Push a new instruction on to the instruction queue
void Program::push_instruction(Instruction * instruction) {
	instructions->push(instruction);
}

// Initialize a new global program
GlobalProgram::GlobalProgram() : Program(NULL) {
	this->functions = new std::unordered_map<std::string, Function *>();
}

// Get the function in global program with [name]
// return 0 on error or if function could not be found within scope
Function * GlobalProgram::get_function(std::string name) {
	std::unordered_map<std::string, Function *>::iterator it;

	it = functions->find(name);

	// Look for function in functions map
	if(it != functions->end())
		return it->second;

	return 0;
}

Function * GlobalProgram::get_function(char * name) {
	return get_function(std::string(name));
}
