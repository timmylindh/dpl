/*
 * instruction.h
 *
 *  Created on: 17 nov. 2017
 *      Author: eatit
 */

#ifndef MEM_INSTRUCTION_H_
#define MEM_INSTRUCTION_H_

#include <vector>
#include "variable.h"

class Function;
class Token;

#define TYPE_FUNCTIONCALL 1
#define TYPE_ASSIGNMENT 2

class Instruction {

public:
	Instruction(int type);

	// The type of instruction
	const int type;

};

// Defines a call to a function
class FunctionCall : public Instruction {

public:
	FunctionCall(Function * function);

	// The function assoiciated with the instruction
	Function * function;

};

// Defines a variable assignment
class Assignment : public Instruction {

public:
	Assignment(Variable * var, int operation);

	int operation;
	Variable * variable;

};

#endif /* MEM_INSTRUCTION_H_ */
