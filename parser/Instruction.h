/*
 * Instruction.h
 *
 *  Created on: 27 aug. 2017
 *      Author: timmy
 */

#ifndef PARSER_INSTRUCTION_H_
#define PARSER_INSTRUCTION_H_

#include "Program.h"
#include "../dtypes.h"

class Instruction : public Program {

	public:
		d_uint type;

		Instruction(Program * parent, d_uint type);

};

#endif /* PARSER_INSTRUCTION_H_ */
