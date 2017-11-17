/*
 * error.h
 *
 *  Created on: 14 nov. 2017
 *      Author: timmy.lindholm
 */

#ifndef ERROR_H_
#define ERROR_H_

// Macro to output an error and cease execution if
// the type is of error
#define ERROR(error_type, format, ...) {printf(error_type ? "Warning: " : "Error: "); printf(format, __VA_ARGS__);  if(! error_type) exit(0);}

#define T_CRIT 0
#define T_WARNING 1

#endif /* ERROR_H_ */
