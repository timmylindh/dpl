/*
 * Program.h
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <map>
#include <vector>
#include <iostream>
#include "../dtypes.h"

using std::map;
using std::string;
using std::vector;

// Defines a function or global variable
class Variable {

	public:
		string name; // Variable name
		vector<d_uint> * Types; // Variable types
		vector<d_uint> * History; // Variable types history in order

		Variable(string name);
};

// Defines a program
class Program {

	public:
		map<const string, Program *> * Functions; // Functions
		map<const string, Variable *> * Variables; // Member variables
		vector<Program *> * Instructions; // Instructions in program
		Program * parent; // Parent program

		Program(Program * parent);
		virtual ~Program();

	private:
};

// Defines a function
class Function : public Program {

	public:
		string name; // Function name
		vector<d_uint> * Return_types; // Function return types
		vector<d_uint> * History; // Function return types history in order

		Function(Program * parent, string name);
};

#endif /* PROGRAM_H_ */
