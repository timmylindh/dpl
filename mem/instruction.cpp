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

// Initialize if statement instruction
IfStatement::IfStatement(std::vector<Token *> * expression, Program * program)
: Instruction(TYPE_IF_STATEMENT) {
	this->expression = expression;
	this->program = program;
}

// Initialize return instruction
ReturnOperation::ReturnOperation(std::vector<Token *> * value)
: Instruction(TYPE_RETURN) {
	this->value = value;
}
