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

