/*
 * DParser.h
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <array>
#include "../dtypes.h"
#include "../lexer/Lexer.h"
#include "Program.h"

using std::string;
using std::cout;
using std::endl;

class Parser {

	public:
		virtual d_uint parse(d_string * code, Program * program);

		Parser(Lexer * lexer, Program * global_program);
		virtual ~Parser();

	private:
		Lexer * lexer;
		Program * program;
		Program * global_program;

		d_uint parse_expr(d_string * code, string * expr); // Parse a expression, return the type
		void ins_assignment(d_string * code, string name, d_uint type); // Assignment instruction
		void ins_function_def(d_string * code, string name); // Function definiton instruction
		d_uint ins_function_call(d_string * code, string name); // Function call instruction and return return type
		Variable * fetch_variable(string name); // Fetch variable from current or global scope
		Function * fetch_function(string name); // Fetch function from current or global scope
		string get_function_args(d_string * code, std::vector<string> * args); // Parse and fetch function arguments
		Token * parse_token_name(d_string * code, Token * tok, d_uint * type, std::vector<d_uint> allowed_types); // Parse a name token. If function set type to return type, if variable set to var type
		d_uint validate_type(std::vector<d_uint> types, d_uint type); // Validate that the type of a object is valid
};

#endif /* PARSER_H_ */
