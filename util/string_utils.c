/**
 * string_utils.c
 *
 *  Created on: Jun 29, 2009
 *      Author: carr
 */

/******************************************************************************/
/*        Copyright (c) 1990, 1991, 1992, 1993, 1994 Rice University          */
/*                           All Rights Reserved                              */
/******************************************************************************/
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <util/general.h>

#include <util/string_utils.h>

/**
 *
 * Save a string into a new chunk of memory
 *
 * @param str a C character string
 * @return a new copy of the string
 */
char* ssave(const char* const str)
{
  register int length = strlen(str) + 1;

  char* nstr = (char*)malloc(length);
  bcopy(str, nstr, length);

  return nstr;
}

/**
 *
 * Free the memory for str
 *
 * @param str a C character string
 */
void sfree(char *str)
{
  free((void*)str);

  return;
}
/**
 *
 * Move a string
 *
 * @param old a pointer to a C string
 * @param fresh a new C string
 */
void smove(char **old, char *fresh)
{
  sfree(*old);
  *old = ssave(fresh);

  return;
}

/**
 *
 *  string_copy - just like strcpy, but instead of returning pointer to beginning of s1,
 *      it returns a pointer to the null that terminates s1.
 *
 * @param s1 a C character string
 * @param s2 a C character string
 * @return a pointer to the null character that terminates s1
 */
static char* string_copy(register char* s1, register char* s2)
{
  while ((*s1++ = *s2++) != 0);

  return --s1;
}

/**
 *
 * nssave(n,s1,...,sn) - concatenate n strings into a dynamically allocated
 * blob, and return a pointer to the result. "n" must be equal to the # of
 * strings. The returned pointer should be freed with sfree().
 *
 * @param n the number of strings to concatenate
 * @param s1 a variable number of C character strings
 * @return a pointer to the concatenated strings
 */
char* nssave(int n, const char* const s1, ...)
{
  va_list ap;
  register int i;
  register int nb = 0; /* the length of the result, hence the number of bytes to allocate */
  register char *tstr; /* to use while concatenating */
  register char *nstr; /* the result */

    /* Count up all the bytes in all the strings, so we know how much to allocate. */
  va_start(ap, s1);
  nb = strlen(s1);
  for (i = 0; i < n-1; i++) nb += strlen(va_arg(ap, char*));
  va_end(ap);

  tstr = nstr = (char*)malloc(nb+1);

    /* Concat them all together into the new space. */
  va_start(ap, s1);
  tstr = string_copy(tstr, (char *) s1);
  for (i = 0; i < n-1; i++) tstr = string_copy(tstr, va_arg(ap, char*));
  va_end(ap);

  return nstr;
}


/**
 *
 * nscat(n,s1,...,sn) - concatenate n strings into a dynamically allocated
 * blob, and return a pointer to the result. "n" must be equal to the # of
 * strings. The n strings are freed with sfree().  The returned pointer
 * should be freed with sfree().
 *
 * @param n the number of strings to concatenate
 * @param s1 a variable number of C character strings
 * @return a pointer to the concatenated strings
 */
char* nscat(int n, char* s1, ...)
{
  va_list ap;
  register int  i;
  register int  nb = 0; /* the length of the result, hence the number of bytes to allocate */
  register char *as;    /* one of the argument strings */
  register char *tstr;  /* to use while concatenating */
  register char *nstr;  /* the result */

    /* Count up all the bytes in all the strings, so we know how much to allocate. */
  va_start(ap, s1);
  nb = strlen(s1);
  for (i = 0; i < n-1; i++) nb += strlen(va_arg(ap, char*));
  va_end(ap);

  tstr = nstr = (char*)malloc(nb+1);

    /* Concat all strings into the new space, freeing them after they have been copied.  */
  va_start(ap, s1);
  tstr = string_copy(tstr, s1);
  sfree(s1);
  for (i = 0; i < n-1; i++)
    {
       as = va_arg(ap, char*);
       tstr = string_copy(tstr, as);
       sfree(as);
    }
  va_end(ap);

  return nstr;
}

/**
 *
 *   Returns a temporary string made up from the sprintf()
 *  style variable arguments.  The string is destroyed by
 *  the next call to this fuction.
 *
 * @param buf a C character string storing the result
 * @param size the size of the buffer
 * @param arg_list a variable number of character strings
 * @return the resulting string
 */
char* string_print(char* buf, int size, va_list arg_list)
{
  char* format;  /* the format string */

  format = va_arg(arg_list, char*);
  vsprintf(buf, format, arg_list);

  return buf;
}

/**
 *
 *  locate the first occurrence of string s2 within s1.
 *  behaves properly for null s1.
 *  returns -1 for no match.
 *
 * @param s1 a C character string
 * @param s2 a C character string
 * @return the index of the first occurence of s2 within s1, -1 if not found
 */
int find(char s1[], char s2[])
{
  int l1, l2, i, j;
  bool match;

  l1 = strlen(s1);
  l2 = strlen(s2);
  for (i = 0; i <= l1-l2; i++)
    {
       match = true;
       for (j = 0; match && (j < l2); j++) if (s1[i+j] != s2[j]) match = false;
       if (match) return i;
    }

  return -1;
}

/**
 *
 *  finds first occurrence of any character in s2 within s1.
 *  returns index of null terminator for no match
 *  (i.e., f_c_of("cat","dog") ==> 3 ( = strlen("cat"))).
 *
 * @param s1 a C character string
 * @param s2 a C character string
 * @return the index of the first occurence of any character in s2 in s1, -1 if not found
 */
int find_char_of(char s1[], char s2[])
{
  int l1, l2, i, j;
  bool match;
  char c1;

  l1 = strlen(s1);
  l2 = strlen(s2);
  for (i = 0; i <l1; i++)
    {
       match = false;
       c1 = s1[i];
       for (j = 0; !match && (j < l2); j++) if (c1 == s2[j]) match = true;
       if (match) return i;
    }

  return i;
}

/**
 *
 * counts occurrences of characters in s2 within s1.
 *
 * @param s1 a C character string
 * @param s2 a C character string
 * @return the number of occurences of characters in s2 found in s1
 */
int char_count(char s1[], char s2[])
{
  int l1, l2, i, j, count;
  char c1;

  l1 = strlen(s1);
  l2 = strlen(s2);
  count = 0;
  for (i = 0; i < l1; i++)
    {
       c1 = s1[i];
       for (j = 0; j < l2; j++) if (c1 == s2[j]) count++;
    }

  return count;
}

/**
 *
 *rindex3 - like rindex, but takes a third argument, "at", which points at the
 * location within the string "str" to begin looking for "ch". Basically, this
 * avoids a strlen() every time we do a rindex().
 *
 * @param str a C character string
 * @param ch a character
 * @param at a character
 * @return the rightmost index of ch in str starting at 'at'
 */
char* rindex3(register char* str, register char ch, register char* at)
{
     /* Walk backward, looking for ch. */
  while (*at != ch)
  if (--at < str) return (char*) 0;

  return at;
}

/**
 *
 * returns a substring from s1 starting at start to the end.
 *
 * @param s1 a C character string
 * @param start an index into s1
 * @return the substring from s1 beginning at 'start'
 */
char* strtail(char s1[], int start)
{
  int i, length;
  char* s2;

  length = strlen(s1);
  if (start < 0) start = 0;
  else if (start > length) start = length;
  length = length - start;

  s2 = (char*)malloc(length + 1);

  for (i = 0; i < length; i++) s2[i] = s1[start+i];
  s2[i] = (char)0;

  return s2;
}

/**
 *
 *  returns a substring from s1 starting at start containing UP TO
 *  length characters (less if the end is swallowed).
 *
 * @param s1 a C character string
 * @param start an index into s1
 * @param his_length the max number of characters allowed in the substring
 * @return a substring of s1 starting at 'start' with a max 'his_length' characters
 */
char* substr(char s1[], int start, int his_length)
{
  int i, length;
  char* s2;

  length = strlen(s1);
  if (start < 0) start = 0;
  else if (start > length) start = length;
  length = length - start;

    /* negative length means distance from end of string */
  if (his_length < 0) his_length += length;

    /* always choose shortest string */
  length = MIN(his_length,length);
  length = MAX(length,0);

  s2 = (char*)malloc(length + 1);

  for (i = 0; i < length; i++) s2[i] = s1[start+i];
  s2[i] = (char)0;

  return s2;
}

/**
 *
 * Create a hash of a string
 *
 * @param string a character string
 * @param size the maximum hash value
 * @return a hash of a string
 */
int hash_string(register char* string, int size)
{
  register unsigned int result = 0;
  unsigned char c;

  while(*string != 0)
    {
       c = (unsigned char) *string++;
       result += (c & 0x3f);
       result = (result << 5) + (result >> 27);
    }

  return (result % size);
}

/**
 *
 * Convert a string to lower case
 *
 * @param string a C character string
 * @return a lowercase only string
 */
char* strlower (char *string)
{
  register char* s = string;
  register char c;

  while ((c = *s))
    {
       if (isupper(c)) *s = tolower(c);
       s++;
    }

  return string;
}

/**
 *
 * Convert a string to upper case
 *
 * @param string a C character string
 * @return an uppercase only string
 */
char* strupper (char* string)
{
  register char* s = string;
  register char c;

  while ((c = *s))
    {
       if (islower(c)) *s = toupper(c);
       s++;
    }

  return string;
}

/**
 *
 * returns index of first non-blank character in string, starting at at
 * e.g., eat_space("0123  6",4) returns 6
 *
 * @param string a C character string
 * @param at an index into 'string'
 * @return index of first non-black character in 'string' starting at 'at'
 */
int eat_space (register char* string, register int at)
{
  string = &string[at];

  while (isspace(*string))
    {
       at++;
       string++;
    }

  return at;
}

/**
 *
 * Convert a character to lower case
 *
 * @param c a character
 * @return the lower case equivalent of 'c'
 */
char to_lower(char c)
{
  if (isupper(c)) return tolower(c);
  else            return c;
}


/**
 *
 * gobble string if it matches target, ignoring blanks in string
 * start at j, return index of first character past the end
 * e.g, gobble(".true."," .true.   ") returns 10 (index of the terminating zero
 *
 * @param target a C character string
 * @param string a C charater string
 * @param j an index into 'string'
 * @return see above
 */
int gobble(char* target, char* string, int j)
{
  char c = *target;
  int i = eat_space(string, j);

  while (c != 0 && c == to_lower(string[i]))
    {
       i = eat_space(string, i+1);
       c = *(++target);
    }

  if (c == 0) return i;
  else        return j;
}

/**
 *
 * return 1 if target matches string[i:*] - blanks
 *
 * @param target a C character string
 * @param string a C character string
 * @param i an index into 'string'
 * @return see above
 */
int fmatch(char* target, char* string, int i)
{
  char c = *target;

  i = eat_space(string, i);

  while (c != 0 && c == to_lower(string[i]))
    {
       i = eat_space(string, i+1);
       c = *(++target);
    }

  if (c == 0) return 1;
  else        return 0;
}

