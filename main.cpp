/*
 * main.cpp
 *
 *  Created on: 14 nov. 2017
 *      Author: timmy.lindholm
 */

#include "compiler.h"

int main() {
	Compiler compiler;
	compiler.compile((char * const) "test.dpsl");
}



