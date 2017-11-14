/*
 * Compiler.cpp
 *
 *  Created on: 13 nov. 2017
 *      Author: timmy.lindholm
 */

#include <cstdio>
#include <cstdlib>

#include <iostream>

#include "error.h"
#include "compiler.h"

#define READ_FILE_ERROR 1

Compiler::Compiler() {

	this->parser = new Parser();
	this->buffer = NULL;
}

Compiler::~Compiler() {
	// TODO Auto-generated destructor stub
}

// Compile a file specified by the argument
int Compiler::compile(char * file_name) {
	try {
		this->buffer = this->read_file(file_name);
	} catch(int e) {
		ERROR(1, "%s", "failed");
		exit(0);
	}

	printf("%s\n", this->buffer);

	return 1;
}

/* Opens a file and reads the content into a buffer
 * Throws an error if file could not be opened
 */
char * Compiler::read_file(char * file_name) {
	FILE * file_stream;
	char * buffer, * pbuffer;

	if(! (file_stream = fopen(file_name, "r")))
		throw READ_FILE_ERROR;

	buffer = (char *) malloc(200 * sizeof(char));
	pbuffer = buffer;

	int n_total_read = 0;
	int n_read = 0;

	while((n_read = fread(pbuffer, sizeof(char), 200, file_stream)) == 200) {
		n_total_read += n_read;

		buffer = (char *) realloc(buffer, n_total_read * sizeof(char));
		pbuffer = buffer + n_total_read;
	}

	pbuffer += n_read;
	pbuffer[n_total_read] = '\0';

	fclose(file_stream);
	return buffer;
}
