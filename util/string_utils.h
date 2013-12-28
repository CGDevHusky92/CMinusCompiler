/*
 * string_utils.h
 *
 *  Created on: Jun 29, 2009
 *      Author: carr
 */

/******************************************************************************/
/*        Copyright (c) 1990, 1991, 1992, 1993, 1994 Rice University          */
/*                           All Rights Reserved                              */
/******************************************************************************/

#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_

/*  This is the Rn string header file.  The standard Unix entry points have  */
/*  been removed to be compatible with C++.  If you wish to use the	     */
/*  standard string functions, please include /usr/include/string.h.         */

#include <util/general.h>

#include <stdarg.h>

#define STREQ(x,y) ((*(x) == *(y)) && !strcmp((x), (y)))

EXTERN(char*, ssave, (const char *const str));
EXTERN(void, sfree, (char* str));
EXTERN(void, smove, (char** old_str, char* new_str));
EXTERN(char*, nscat, (int n, char* s1, ...));
EXTERN(char*, nssave, (int n, const char *const s1, ...));
EXTERN(char*, string_print, (char* buf, int size, va_list arg_list));
EXTERN(int, find, (char s1[], char s2[]));
EXTERN(int, find_char_of, (char s1[], char s2[]));
EXTERN(int, char_count, (char s1[], char s2[]));
EXTERN(char*, rindex3, (char* str, char ch, char* at));
EXTERN(char*, strtail, (char s1[], int start));
EXTERN(char*, substr, (char s1[], int start, int his_length));
EXTERN(int, hash_string, (char* string, int size));
EXTERN(char*, strlower, (char* string));
EXTERN(char*, strupper, (char* string));
EXTERN(int, eat_space, (char* string, int at));
EXTERN(char, to_lower, (char c));
EXTERN(int, gobble, (char* target, char* string, int j));
EXTERN(int, fmatch, (char* target, char* string, int i));


#endif /* STRING_UTILS_H_ */
