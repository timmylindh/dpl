/*
 * DCompiler.h
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

#ifndef COMPILER_H_
#define COMPILER_H_

#include "dtypes.h"
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "translator/Translator.h"

class Compiler {

	private:
		d_string code;

		Lexer * lexer;
		Parser * parser;
		Translator * translator;

	public:
		Compiler();
		void compile(d_string code);
		virtual ~Compiler();

};

#endif /* COMPILER_H_ */
