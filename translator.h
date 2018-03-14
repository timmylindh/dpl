/*
 * Translator.h
 *
 *  Created on: 12 dec. 2017
 *      Author: eatit
 */

#ifndef TRANSLATOR_H_
#define TRANSLATOR_H_

#include <unordered_map>
#include "mem/program.h"
#include "mem/function.h"

class Translator {

public:
	Translator();

	// Translate a program
	void translate(Program * program);

private:
	Program * program;

	// Return types
	std::unordered_map<int, std::string> types;

	// Output the default C includes
	void default_includes();

	// Translate global function definitions in to their code form
	void translate_global_function_prototypes();

	// Define the main method of the application
	void define_main();

	// Declare the variables in program
	void declare_variables(Program * program);

	// Main function for translation of an instruction
	void translate_instruction(Instruction * instruction);

	// Translate an assignment operation
	void translate_assignment_operation(Assignment * instruction);

	// Translate a return operation
	void translate_return_operation(ReturnOperation * instruction);

	// Translate an if statement
	void translate_if_statement(IfStatement * instruction);

	// Translate a function call
	void translate_function_call(FunctionCall * instruction);

	// Translate inline injection code operation
	void translate_inline_injection(InlineInjection * instruction);

	// Define global functions
	void define_global_functions();
};

#endif /* TRANSLATOR_H_ */
