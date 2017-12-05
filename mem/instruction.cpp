/*
 * instruction.cpp
 *
 *  Created on: 17 nov. 2017
 *      Author: eatit
 */

#include "instruction.h"

Instruction::Instruction(int type) : type(type) {

}

// Initialize a function call instruction
FunctionCall::FunctionCall(Function * function) : Instruction(TYPE_FUNCTIONCALL) {
	this->function = function;
}

// Initialize a assignment instruction
Assignment::Assignment(Variable * var, int operation) : Instruction(TYPE_ASSIGNMENT) {
	this->variable = var;
	this->operation = operation;
}
