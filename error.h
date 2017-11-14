/*
 * error.h
 *
 *  Created on: 14 nov. 2017
 *      Author: timmy.lindholm
 */

#ifndef ERROR_H_
#define ERROR_H_

// Macro to output an error and cease execution
#define ERROR(error_type, format, ...) {printf("error: "); printf(format, __VA_ARGS__); exit(0);}

#endif /* ERROR_H_ */
