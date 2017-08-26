/*
 * DCompiler.cpp
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

#include <iostream>

#include "Compiler.h"
#include "Program.h"

Compiler::Compiler() {
	this->code = NULL;

	// Initialize compiler objects
	this->lexer = new Lexer();
	this->parser = new Parser(this->lexer);
	this->translator = new Translator();
}

Compiler::~Compiler() {

}

// Start code compilation
void Compiler::compile(d_string code) {
	d_uint pos;
	d_string translation;

	this->code = code;

	// Parse a single instruction, or a set of instructions
	while((pos = this->parser->parse(this->code, this->program_tree)))
		this->code += pos;

	// Translate program
	translation = this->translator->translate(program_tree);

	std::cout << translation << std::endl;
}


