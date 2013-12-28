/**
 * general.h
 *
 *  Created on: Jun 29, 2009
 *      Author: carr
 */

#ifndef GENERAL_H_
#define GENERAL_H_

typedef	void*	Generic;		/**< a pointer to anything */

#ifndef false
typedef enum {false = 0,true = 1} bool; /**< C boolean values */
#else
typedef int bool;
#endif

/* ANSI C Definitions */

#define EXTERN(rettype, name, arglist) rettype name arglist /**< a macro for declaring global function prototypes */
#define STATIC(rettype, name, arglist) static rettype name arglist /**< a macro for declaring static function prototypes */
#define FUNCTION_POINTER(rettype, name, arglist) rettype(*name)arglist /**< a macro for declaring function parameters */

/* Commonly used function definitions and Macros */

#define	UNUSED		(-1)	 /* Often used magic number		*/

#define	MIN(a,b) (((a)<(b))?(a):(b)) /**< a macro for returning the minimum of two numbers */
#define	MAX(a,b) (((a)>(b))?(a):(b)) /**< a macro for returning the maximum of two numbers */

#endif /* GENERAL_H_ */
