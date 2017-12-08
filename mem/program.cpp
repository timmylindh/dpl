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

// Get the variable [name] in current program
// return 0 if it does not exist
Variable * Program::get_variable(std::string name) {
	std::unordered_map<std::string, Variable *>::iterator it;

	if((it = variables->find(name)) == variables->end())
		return 0;

	return it->second;
}

// Add variable [name] to current program
void Program::push_variable(Variable * var) {
	variables->insert(std::pair<std::string, Variable *>(std::string(var->name), var));
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

// Push a function to the function map
// [name] variable to prevent error because of forward declaration
void GlobalProgram::push_function(const char * name, Function * function) {
	functions->insert(std::pair<std::string, Function *>(std::string(name), function));
}
