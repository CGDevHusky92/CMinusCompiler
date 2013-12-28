/*
 * symtab.h
 *
 *  Created on: Jun 29, 2009
 *      Author: carr
 */

/******************************************************************************/
/*        Copyright (c) 1990, 1991, 1992, 1993, 1994 Rice University          */
/*                           All Rights Reserved                              */
/******************************************************************************/

#ifndef SYMTAB_H_
#define SYMTAB_H_

#include <util/general.h>

typedef struct SymTable_internal_structure *SymTable;

EXTERN(SymTable, SymInit, (unsigned int size));
EXTERN(void, SymKill, (SymTable ip));

EXTERN(int, SymMaxIndex, (SymTable ip));
EXTERN(int, SymIndex, (SymTable ip, char *name));
EXTERN(int, SymQueryIndex, (SymTable ip, char *name));

EXTERN(Generic, SymGetFieldByIndex, (SymTable ip, int index, char *field));
EXTERN(Generic, SymGetField, (SymTable ip, char *name, char *field));

EXTERN(void, SymPutFieldByIndex, (SymTable ip, int index, char *field, Generic val));
EXTERN(void, SymPutField, (SymTable ip, char *name, char *field, Generic val));

typedef FUNCTION_POINTER(void, SymCleanupFunc, (Generic val));
EXTERN(void, SymInitField, (SymTable ip, char *field, Generic val, SymCleanupFunc cleanup));
EXTERN(void, SymKillField, (SymTable ip, char *field));

EXTERN(int, SymFieldExists, (SymTable ip, char *field));

typedef FUNCTION_POINTER(void, SymIteratorFunc, (SymTable ip, int index, Generic extra_arg));
EXTERN(void, SymForAll, (SymTable ip, SymIteratorFunc func, Generic extra_arg));

EXTERN(void, SymDumpEntryByIndex,(SymTable ip, int index));
EXTERN(void, SymDump, (SymTable ip));

#define SYM_INVALID_INDEX  -1
#define SYM_NAME_FIELD     "name"

#endif /* SYMTAB_H_ */
