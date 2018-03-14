/*
 * Translator.cpp
 *
 *  Created on: 12 dec. 2017
 *      Author: eatit
 */

#include <stack>
#include "translator.h"

Translator::Translator() {

	this->program = NULL;

	// Define return types
	types[TOK_INT] = "int";
	types[TOK_FLOAT] = "float";
	types[TOK_STRING] = "char *";
	types[TOK_NULL] = "void *";
	types[TOK_AUTO] = "auto";

}

// Takes in a program as argument and translates it
void Translator::translate(Program * program) {
	this->program = program;

	// Print default includes
	default_includes();

	// Print global variable declarations
	declare_variables(program);

	// Handle global function definitions
	translate_global_function_prototypes();

	// Define global functions
	define_global_functions();

	// Define main function
	define_main();

}

// Output the default C includes
void Translator::default_includes() {
	std::cout << "#include <iostream>" << std::endl;
	std::cout << "#include <string>" << std::endl;
	std::cout << "#include <stdio.h>" << std::endl;
	std::cout << "#include <stdlib.h>" << std::endl;
}

// Translate the global function protoypes in programs into their code form
void Translator::translate_global_function_prototypes() {
	GlobalProgram * program;

	program = static_cast<GlobalProgram *>(this->program);

	// Iterate through each function initializer
	for(auto function = program->functions->begin(); function != program->functions->end(); function++) {
		std::string return_type = types[function->second->get_return_type()];
		std::string name = function->second->name;
		std::string arguments;

		// Fetch arguments
		Argument * arg;
		int args_size = function->second->get_arguments_size();

		if(args_size) {

			for(int i = 0; i < args_size; i++) {
				arg = function->second->get_next_argument();

				arguments += types[arg->type] + " " + arg->name + ((i == args_size - 1) ? "" : ",");
			}

		}

		std::cout << return_type << " " << name << "(" << arguments << ");" << std::endl;
	}
}

// Define the main function, which is the entry point for every program
void Translator::define_main() {
	Instruction * ins;

	std::cout << std::endl << "int main() {" << std::endl;

	// Iterate through global instructions
	while((ins = program->get_next_instruction()))
		translate_instruction(ins);

	// End of main function
	std::cout << "return 0;" << std::endl << "}" << std::endl;
}

// Declare the variables in program
void Translator::declare_variables(Program * program) {

	// Iterate through the variables
	for(auto var = program->variables->begin(); var != program->variables->end(); var++) {
		std::cout << types[var->second->type] <<  " " << var->second->name << ";" << std::endl;
	}

	std::cout << std::endl;
}

// Translate an instruction into its source form
void Translator::translate_instruction(Instruction * instruction) {

	switch(instruction->type) {

	// Assignment operation
	case TYPE_ASSIGNMENT:
		translate_assignment_operation(static_cast<Assignment *>(instruction));

		break;

	// Return operation
	case TYPE_RETURN:
		translate_return_operation(static_cast<ReturnOperation *>(instruction));

		break;

	// If statement
	case TYPE_IF_STATEMENT:
		translate_if_statement(static_cast<IfStatement *>(instruction));

		break;

	// Function call
	case TYPE_FUNCTIONCALL:
		translate_function_call(static_cast<FunctionCall *>(instruction));

		break;

	// Inline code injection
	case TYPE_INLINE_INJECTION:
		translate_inline_injection(static_cast<InlineInjection *>(instruction));

		break;
	}

}

// Translate an assignment operation in postfix notation
void Translator::translate_assignment_operation(Assignment * instruction) {
	std::cout << instruction->variable->name << " = ";

	for(auto tok : *instruction->variable->value) {
		std::cout << tok->value;
	}

	std::cout << ";" << std::endl;
}

// Translate a return operation
void Translator::translate_return_operation(ReturnOperation * instruction) {
	std::cout << "return ";

	for(auto tok : *instruction->value) {
		std::cout << tok->value;
	}

	std::cout << ";" << std::endl;
}

// Translate an if statement
void Translator::translate_if_statement(IfStatement * instruction) {
	std::cout << "if (";

	for(auto tok : *instruction->expression) {
		std::cout << tok->value;
	}

	std::cout << ") {" << std::endl;

	// Iterate through instructions
	Instruction * ins;

	while((ins = instruction->program->get_next_instruction())) {
		translate_instruction(ins);
	}

	std::cout << "}" << std::endl;
}

// Translate a function call
void Translator::translate_function_call(FunctionCall * instruction) {
	std::vector<Token *> * arg;
	int first = 1;

	std::cout << instruction->function->name << "(";

	while((arg = instruction->get_next_argument())) {

		if(first)
			first = 0;
		else
			std::cout << ",";

		for(auto tok : *arg)
			std::cout << tok->value;

	}

	std::cout << ");" << std::endl;

}
// Define global functions
void Translator::define_global_functions() {
	GlobalProgram * program;

	program = static_cast<GlobalProgram *>(this->program);

	std::cout << std::endl;

	// Iterate through each function initializer
	for(auto function = program->functions->begin(); function != program->functions->end(); function++) {
		std::string return_type = types[function->second->get_return_type()];
		std::string name = function->second->name;
		std::string arguments;

		// Fetch arguments
		Argument * arg;
		int args_size = function->second->get_arguments_size();

		if(args_size) {

			for(int i = 0; i < args_size; i++) {
				arg = function->second->get_next_argument();

				arguments += types[arg->type] + " " + arg->name + ((i == args_size - 1) ? "" : ",");
			}

		}

		std::cout << return_type << " " << name << "(" << arguments << ") {" << std::endl;

		// Declare variables
		declare_variables(function->second);

		// Iterate through instructions
		Instruction * ins;

		while((ins = function->second->get_next_instruction()))
			translate_instruction(ins);

		std::cout << std::endl << "}" << std::endl << std::endl;
	}
}

// Translate inline injection operation
void Translator::translate_inline_injection(InlineInjection * instruction) {
	// Output all tokens
	for(auto tok : *(instruction->code)) {

		if(tok->type == TOK_STRING)
			std::cout << "\"" << tok->value << "\"" << " ";
		else
			std::cout << tok->value << " ";

	}

}

