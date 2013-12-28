#include <stdio.h>
#include <stdlib.h>
#include <util/general.h>
#include <util/symtab.h>
#include <util/dlink.h>
#include <util/string_utils.h>
#include <util/symtab_stack.h>
#include <codegen/symfields.h>
#include <codegen/types.h>
#include <codegen/codegen.h>
#include <codegen/reg.h>

/**
 * Initalize an empty stack of symbol tables
 *
 */
SymtabStack symtabStackInit() {
	int *size = malloc(sizeof(int));
	*size = 0;
	dlinkListAlloc((Generic)size);
}

/**
 * Get the size of the stack
 *
 * @param stack a stack of symbol tables
 * @return the number of elements on the stack of symbol tables
 */
int stackSize(SymtabStack stack) {
	int *size = (int*)dlinkListAtom(stack);
	return *size;
}

/**
 * Push a new symbol table on the stack when entering a new scope region
 *
 * @param stack a stack of symbol tables
 * @return a new symbol table 
 */
SymTable beginScope(SymtabStack stack) {
	SymTable symtab = SymInit(SYMTABLE_SIZE);

	SymInitField(symtab,SYMTAB_OFFSET_FIELD,(Generic)-1,NULL);
	SymInitField(symtab,SYMTAB_REGISTER_INDEX_FIELD,(Generic)-1,NULL);

	int intIndex = SymIndex(symtab,SYMTAB_INTEGER_TYPE_STRING);
    int errorIndex = SymIndex(symtab,SYMTAB_ERROR_TYPE_STRING);
    int voidIndex = SymIndex(symtab,SYMTAB_VOID_TYPE_STRING);

    SymPutFieldByIndex(symtab,intIndex,SYMTAB_SIZE_FIELD,(Generic)INTEGER_SIZE);
    SymPutFieldByIndex(symtab,errorIndex,SYMTAB_SIZE_FIELD,(Generic)0);
    SymPutFieldByIndex(symtab,voidIndex,SYMTAB_SIZE_FIELD,(Generic)0);

    SymPutFieldByIndex(symtab,intIndex,SYMTAB_BASIC_TYPE_FIELD,(Generic)INTEGER_TYPE);
    SymPutFieldByIndex(symtab,errorIndex,SYMTAB_BASIC_TYPE_FIELD,(Generic)ERROR_TYPE);
    SymPutFieldByIndex(symtab,voidIndex,SYMTAB_BASIC_TYPE_FIELD,(Generic)VOID_TYPE);

	dlinkPush(dlinkNodeAlloc((Generic)symtab),stack);
	int *size = (int*)dlinkListAtom(stack);
	(*size)++;

	return symtab;
}

/**
 * Pop a symbol table off of the stack when leave a scope region
 *
 * @param stack a stack of symbol tables
 * @return the symbol table popped off of the stack
 */
SymTable endScope(SymtabStack stack) {
	SymTable symtab = (SymTable)dlinkNodeAtom(dlinkPop(stack));
	int *size = (int*)dlinkListAtom(stack);
	(*size)--;
	return symtab;
}

/**
 * Find the topmost symbol table that contains an entry for a string
 *
 * @param stack a stack of symbol tables
 * @return the symbol table containing the string or null
 */
SymTable findSymtab(SymtabStack stack, char* key) {

	DNode node = dlinkHead(stack);
	while (node != NULL) {
	  if (SymQueryIndex((SymTable)dlinkNodeAtom(node),key) != SYM_INVALID_INDEX)
	    break;
	  node = dlinkNext(node);
	}

	if (node != NULL)
		return (SymTable)dlinkNodeAtom(node);
	else
		return NULL;
}

/**
 * Get the most recently defined symbol table
 *
 * @param stack a stack of symbol tables
 * @return the symbol table on top of the stack
 */
SymTable currentSymtab(SymtabStack stack) {
	return (SymTable)dlinkNodeAtom(dlinkHead(stack));
}

/**
 * Get the symbol table on the bottom of the stack
 *
 * @param stack a stack of symbol tables
 * @return the symbol table on the bottom of the stack
 */
SymTable lastSymtab(SymtabStack stack) {
	return (SymTable)dlinkNodeAtom(dlinkTail(stack));
}
