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
	this->arguments = new std::vector<std::vector<Token *> *>();
}

// Push an argument into the arguments vector
void FunctionCall::push_argument(std::vector<Token *> * argument) {
	arguments->push_back(argument);
}

// Get the next argument in the arguments vector
std::vector<Token *> * FunctionCall::get_next_argument() {
	static int i = 0;
	std::vector<Token *> * arg;

	int len = arguments->size();

	if(i == len) {
		i = 0;
		return 0;
	}

	arg = arguments->at(i++);

	return arg;
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

// Initialize inline injection instruction
InlineInjection::InlineInjection(std::vector<Token *> * code)
: Instruction(TYPE_INLINE_INJECTION) {
	this->code = code;
}
