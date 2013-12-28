/*
 * types.h
 *
 *  Created on: Jul 13, 2009
 *      Author: carr
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <util/general.h>
#include <util/symtab.h>
#include <codegen/symfields.h>

#define INTEGER_SIZE 4	/**< The number of bytes for an integer */
#define VOID_SIZE 4 	/**< The number of bytes for a void value */

#define INTEGER_TYPE 0 /**< an integer */
#define ERROR_TYPE 1
#define VOID_TYPE 2
#define NUM_TYPES 3

#endif /* TYPES_H_ */
