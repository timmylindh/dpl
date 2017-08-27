/*
 * DTranslator.h
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

#ifndef TRANSLATOR_H_
#define TRANSLATOR_H_

#include "../dtypes.h"
#include "../parser/Program.h"

class Translator {

	public:
		d_string translate(Program * program_tree);

		Translator();
		virtual ~Translator();

};

#endif /* TRANSLATOR_H_ */
