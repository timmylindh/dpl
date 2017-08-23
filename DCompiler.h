/*
 * DCompiler.h
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

#ifndef DCOMPILER_H_
#define DCOMPILER_H_

#include "dtypes.h"

class D_Compiler {

	private:
		d_string code;

	public:
		D_Compiler(d_string code);
		void compile();
		virtual ~D_Compiler();

};

#endif /* DCOMPILER_H_ */
