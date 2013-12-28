#ifndef CODEGEN_H_
#define CODEGEN_H_

#define PRINT_INTEGER_FMT ".int_wformat"	/**< The printf code for printing an integer */
#define PRINT_FLOAT_FMT ".float_wformat"	/**< The printf code for printing a float */
#define PRINT_STRING_FMT ".str_wformat"	/**< The printf code for printing a string */
#define READ_INTEGER_FMT ".int_rformat"	/**< The printf code for reading an integer */
#define READ_FLOAT_FMT ".float_rformat"	/**< The printf code for reading a float */
#define SYSCALL_PRINT_INTEGER PRINT_INTEGER_FMT	/**< The syscall code for printing an integer */
#define SYSCALL_PRINT_FLOAT PRINT_FLOAT_FMT	/**< The syscall code for printing a float */
#define SYSCALL_PRINT_STRING PRINT_STRING_FMT 	/**< The syscall code for printing a string */
#define SYSCALL_READ_INTEGER READ_INTEGER_FMT	/**< The syscall code for reading an integer */
#define SYSCALL_READ_FLOAT READ_FLOAT_FMT	/**< The syscall code for reading a float */
#define SYSCALL_EXIT "10"			/**< The syscall code for exiting the interpreter */

/**
 * Data needed for adding variable to the symbol table.
 */
typedef struct AddIdType {
	int typeIndex;			/**< the symbol table index of the type of a list of variables */
	int offset;			/**< the current offset in the activation record */
        SymTable symtab;
} AddIdStruct, *AddIdStructPtr;


EXTERN(void, emitDataPrologue, (DList dataList));
EXTERN(void, emitInstructions,(DList list));

EXTERN(void, emitAssignment, (DList instList, SymTable lsymtab, SymTable rsymtab, int lhsRegIndex, int rhsRegIndex));
EXTERN(void, emitReadVariable, (DList instList, SymTable symtab, int addrIndex));
EXTERN(void, emitWriteExpression,(DList instList,SymTable symtab, int index, char *syscallService));
EXTERN(void, emitWriteString,(DList instList,SymTable symtab, int index, DList dataList));
EXTERN(int, emitIfTest, (DList instList, SymTable symtab, int regIndex));
EXTERN(void, emitEndBranchTarget, (DList instList, SymTable symtab, int endLabelIndex));
EXTERN(int, emitThenBranch, (DList instList, SymTable symtab, int elseLabelIndex));
EXTERN(int, emitWhileLoopLandingPad, (DList instList,SymTable symtab));
EXTERN(int, emitWhileLoopTest, (DList instList, SymTable symtab, int regIndex));
EXTERN(void, emitWhileLoopBackBranch,(DList instList, SymTable symtab, int beginLabelIndex, int endLabelIndex));

EXTERN(int, emitOrExpression, (DList instList, SymTable symtab, int leftOperand, int rightOperand));
EXTERN(int, emitAndExpression, (DList instList, SymTable symtab, int leftOperand, int rightOperand));
EXTERN(int, emitNotExpression, (DList instList, SymTable symtab, int operand));
EXTERN(int, emitEqualExpression, (DList instList, SymTable symtab, int leftOperand, int rightOperand));
EXTERN(int, emitNotEqualExpression, (DList instList, SymTable symtab, int leftOperand, int rightOperand));
EXTERN(int, emitLessEqualExpression, (DList instList, SymTable symtab, int leftOperand, int rightOperand));
EXTERN(int, emitLessThanExpression, (DList instList, SymTable symtab, int leftOperand, int rightOperand));
EXTERN(int, emitGreaterEqualExpression, (DList instList, SymTable symtab, int leftOperand, int rightOperand));
EXTERN(int, emitGreaterThanExpression, (DList instList, SymTable symtab, int leftOperand, int rightOperand));
EXTERN(int, emitAddExpression, (DList instList, SymTable symtab, int leftOperand, int rightOperand));
EXTERN(int, emitSubtractExpression, (DList instList, SymTable symtab, int leftOperand, int rightOperand));
EXTERN(int, emitMultiplyExpression, (DList instList, SymTable symtab, int leftOperand, int rightOperand));
EXTERN(int, emitDivideExpression, (DList instList, SymTable symtab, int leftOperand, int rightOperand));

EXTERN(int, emitComputeArrayAddress, (DList instList, SymTable vsymtab, SymTable symtab, char *varName, int subIndex));
EXTERN(int, emitComputeVarAddress,(DList instList, SymTable lsymtab, SymTable symtab, char* varName));
EXTERN(int, emitLoadVariable,(DList instList, SymTable lsymtab, SymTable symtab, int varIndex));
EXTERN(int, emitLoadIntegerConstant,(DList instList, SymTable symtab, int intIndex));

EXTERN(void, emitStartFunction,(DList instList, int offset));
EXTERN(int, emitCallFunction,(DList instList, SymTable symtab, char *func));
EXTERN(void, emitReturnFunction, (DList instList, SymTable lsymtab, SymTable symtab, int funcIndex));
EXTERN(void, emitEndFunction,(DList instList));

EXTERN(void, emitTest,(DList instList, char *test));

EXTERN(void, addIdToSymtab,(DNode node,AddIdStructPtr data));
EXTERN(bool,  isArrayType, (SymTable symtab, int typeIndex));
#endif /*CODEGEN_H_*/

