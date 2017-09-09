/*
 * Instruction.cpp
 *
 *  Created on: 27 aug. 2017
 *      Author: timmy
 */

#include "Instruction.h"

// Initialize a new instruction
Instruction::Instruction(Program * parent, d_uint type) : Program(parent) {
	this->type = type;
}

// Assignment instruction
I_Assignment::I_Assignment(Program * parent, d_uint type) : Instruction(parent, type) {
	this->assign_type = 0;
}

// Function call instruction
I_Function_Call::I_Function_Call(Program * parent, d_uint type) : Instruction(parent, type) {

}
