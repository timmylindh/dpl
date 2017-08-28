/*
 * DCompiler.cpp
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

#include <iostream>

#include "Compiler.h"
#include "parser/Program.h"

Compiler::Compiler() {
	this->code = NULL;

	// Initialize compiler objects
	this->lexer = new Lexer();
	this->parser = new Parser(this->lexer);
	this->translator = new Translator();

	this->program_tree = new Program(NULL);
}

Compiler::~Compiler() {

}

// Start code compilation
void Compiler::compile(d_string code) {
	d_uint pos;
	d_string translation;

	this->code = code;

	// Parse a single instruction, or a set of instructions
	while(this->parser->parse(&this->code, this->program_tree));

	// Translate program
	translation = this->translator->translate(program_tree);

	std::cout << translation << std::endl;
}


