/*
 * Error.cpp
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

#include "Error.h"


// Define a new error
Error::Error(d_uint nr, std::string error) {
	this->error_nr = nr;
	this->error = error;
}


Error::~Error() {

}

// Get the error message
std::string Error::get_error() {
	return this->error;
}

// Parse an error, cease execution
void ERROR(Error * err) {
	std::cout << "Error: " << err->get_error() << std::endl;
	exit(0);
}

// Parse a warning
void ERROR(Warning * err) {
	std::cout << "Warning: " << err->get_error() << std::endl;
}
