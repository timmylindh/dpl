/*
 * instruction.h
 *
 *  Created on: 17 nov. 2017
 *      Author: eatit
 */

#ifndef MEM_INSTRUCTION_H_
#define MEM_INSTRUCTION_H_

class Function;

#define TYPE_FUNCTIONCALL 1

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

#endif /* MEM_INSTRUCTION_H_ */
