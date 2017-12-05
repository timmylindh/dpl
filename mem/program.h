/*
 * program.h
 *
 *  Created on: 17 nov. 2017
 *      Author: eatit
 */

#ifndef MEM_PROGRAM_H_
#define MEM_PROGRAM_H_

#include <unordered_map>
#include <queue>

#include "variable.h"
#include "instruction.h"

class Function;

class Program {

public:

	// Initializor, pass the parent program as parameter
	Program(Program * parent_program);

	/*
	 * Defines the parent program, for instance the main program for a global function
	 */
	Program * parent_program;

	// Get the variable [name] in current program
	// return 0 if it does not exist
	Variable * get_variable(std::string name);

	// Get the next instruction
	Instruction * get_next_instruction();

	// Push a new instruction on to the instruction queue
	void push_instruction(Instruction * instruction);

private:

	// Defines a set of variables in the current program scope
	std::unordered_map<std::string, Variable *> * variables;

	// Defines a set of instructions following the FIFO format
	std::queue<Instruction *> * instructions;

};

// Defines a global program, for instance a new file
class GlobalProgram : public Program {

public:
	GlobalProgram();

	// Get the function in global program with [name]
	// return 0 if no function was found
	Function * get_function(std::string name);
	Function * get_function(char * name);

private:

	// Defines a set of functions
	std::unordered_map<std::string, Function *> * functions;

};
#endif /* MEM_PROGRAM_H_ */
