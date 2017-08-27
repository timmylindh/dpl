/*
 * Program.cpp
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

#include "Program.h"

// Initalize object and member variables for program
Program::Program(Program * parent) {
	this->Functions = new map<const string, Program *>;
	this->Variables = new map<const string, Variable *>;
	this->Instructions = new vector<Program *>;

	this->parent = parent;
}

Program::~Program() {
	// TODO Auto-generated destructor stub
}

// Initialize a new function
Function::Function(Program * parent, string name) : Program(parent) {
	this->Return_types = new vector<d_uint>;
	this->History = new vector<d_uint>;

	this->name = name;
}

// Initialize a new variable
Variable::Variable(string name) {
	this->Types = new vector<d_uint>;
	this->History = new vector<d_uint>;

	this->name = name;
}
