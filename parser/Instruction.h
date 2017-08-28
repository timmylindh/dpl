/*
 * Instruction.h
 *
 *  Created on: 27 aug. 2017
 *      Author: timmy
 */

#ifndef PARSER_INSTRUCTION_H_
#define PARSER_INSTRUCTION_H_

#include "Program.h"
#include "../dtypes.h"

// Instruction types
#define INSTRUCTION_ASSIGNMENT 1

class Instruction : public Program {

	public:
		d_uint type;

		Instruction(Program * parent, d_uint type);

};

// Assignment instruction
class I_Assignment : public Instruction {

	public:
		d_uint assign_type;
		string left, right;

		I_Assignment(Program * parent, d_uint type) : Instruction(parent, type) {}

};
#endif /* PARSER_INSTRUCTION_H_ */
