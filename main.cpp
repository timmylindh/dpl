/*
 * main.cpp
 *
 *  Created on: 14 nov. 2017
 *      Author: timmy.lindholm
 */

#include <ctime>
#include <unistd.h>
#include "compiler.h"


int main(int argc, char ** argv) {
	clock_t start = clock();

	// Spawn a child process
	if(fork()) {
		wait(NULL);

		clock_t end = clock();
		std::cout << "\nexecution time: " << (double)(end - start) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;
	}
	else {
		Compiler compiler;
		compiler.compile((char * const) "test.dpl");
	}

}



