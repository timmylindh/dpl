/*
 * main.cpp
 *
 *  Created on: 14 nov. 2017
 *      Author: timmy.lindholm
 */

#include <ctime>
#include "compiler.h"


int main(int argc, char ** argv) {
	Compiler compiler;

	clock_t start = clock();

	compiler.compile((char * const) "test.dpl");

	clock_t end = clock();

	std::cout << "\nexecution time: " << (double)(end - start) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;
}



