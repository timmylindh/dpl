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
		std::cerr << "\nexecution time: " << (double)(end - start) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;
	}
	else {
		Compiler compiler;

		compiler.line_start = (argc >= 3) ? ((int) strtol(argv[2], (char **) NULL, 10) - 1) : 0;
		compiler.compile(argv[1]);
	}

}



