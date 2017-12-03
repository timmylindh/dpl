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
