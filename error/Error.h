/*
 * Error.h
 *
 *  Created on: 23 aug. 2017
 *      Author: timmy
 */

#ifndef ERROR_ERROR_H_
#define ERROR_ERROR_H_

#include "../dtypes.h"
#include <map>
#include <iostream>

// Error numbers (error_nr)
#define ERRNO_STR_DELIM 1 // Missing " delimiter in string
#define ERRNO_UNK 2 // Keyword or sign not recognized, unknown

// Fatal error, stop execution
class Error {

	public:
		virtual std::string get_error();

		Error(const d_uint nr, std::string error);
		virtual ~Error();

	private:
		std::string error;
		d_uint error_nr;
};

// Warning, continue execution if possible
class Warning : public Error {

	public:
		Warning(d_uint nr, std::string error) : Error(nr, error) {}
};

// Error handler functions
void ERROR(Error * err);
void ERROR(Warning * err);


#endif /* ERROR_ERROR_H_ */
