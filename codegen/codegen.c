#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/string_utils.h>
#include <util/symtab.h>
#include <util/dlink.h>
#include "reg.h"
#include "codegen.h"
#include "symfields.h"
#include "types.h"

extern int globalOffset;

/**
 * Print a data declaration to stdout. This function is called by dlinkApply only.
 *
 * @param decl a DNode containing a data declaration
 */
static void printDataDeclaration(DNode decl) {
	printf("%s\n",(char*)dlinkNodeAtom(decl));
}

/**
 * Emit the assembly prologue for a procedure
 */
void emitProcedurePrologue(DList instList,SymTable symtab, int index) {
	char *name = (char*)SymGetFieldByIndex(symtab,index,SYM_NAME_FIELD); 
	char* inst = nssave(2,"\t.globl ",name);
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = nssave(3,"\t.type ",name,",@function");
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = nssave(2,name,":\tnop");
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = ssave("\tpushq %rbp");
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = ssave("\tmovq %rsp, %rbp");
	dlinkAppend(instList,dlinkNodeAlloc(inst));
}

/**
 * Print the assembly prologue that includes the data section, a declaration of main and an allocation of stack space
 * for the main routine.
 *
 * @param dataList a list of data declarations (strings and floats)
 * @param frameSize The number of bytes need for local variables declared in main
 */
void emitDataPrologue(DList dataList) {
	printf("\t.section\t.rodata\n");
	printf("\t.int_wformat: .string \"%%d\\n\"\n");
	printf("\t.float_wformat: .string \"%%f\\n\"\n");
	printf("\t.str_wformat: .string \"%%s\\n\"\n");
	printf("\t.int_rformat: .string \"%%d\"\n");
	printf("\t.float_rformat: .string \"%%f\"\n");
	if (globalOffset != 0)
		printf("\t.comm _gp, %d, 4\n",globalOffset);  
		                                              
	dlinkApply(dataList,(DLinkApplyFunc)printDataDeclaration);
	printf("\t.text\n");
}

/**
 * Print an assembly instruction to stdout. This function is only called by dlinkApply.
 *
 * @param inst a DNode containing an assembly instruction.
 */
static void printInstruction(DNode inst) {
	printf("%s\n",(char*)dlinkNodeAtom(inst));
}

/**
 * Print all of the assembly instructions for the main routine to stdout.
 *
 * @param instList a DList of assembly instructions.
 */
void emitInstructions(DList instList) {
	dlinkApply(instList,(DLinkApplyFunc)printInstruction);
}


void emitExit(DList instList) {

  /*char *inst = ssave("\tmov dword ptr [%esp], 0");
	dlinkAppend(instList,dlinkNodeAlloc(inst));
	inst = ssave("\tcall exit");
	dlinkAppend(instList,dlinkNodeAlloc(inst));*/

  char *inst = ssave("\tleave");
  dlinkAppend(instList,dlinkNodeAlloc(inst));
  inst = ssave("\tret");
  dlinkAppend(instList,dlinkNodeAlloc(inst));
}

/**
 * Add an instruction that performance an assignment.
 *
 * @param instList a DList of assembly instructions
 * @param symtab a symbol table
 * @param lhsRegIndex the symbol table index of the register for the l-value address
 * @param rhsRegIndex the symbol table index of the register for the r-value
 */
void emitAssignment(DList instList, SymTable lsymtab, SymTable rsymtab, int lhsRegIndex, int rhsRegIndex) {
	char *inst;
	int test = 1;
	char *regName = (char*)SymGetFieldByIndex(rsymtab,rhsRegIndex,SYM_NAME_FIELD);
	char *setName = get64bitIntegerRegisterName(rsymtab, lhsRegIndex);
	if (setName == NULL) {
		test = 0;
		setName = get64bitIntegerRegisterName(lsymtab, lhsRegIndex);
	}

	inst = nssave(5,  "\tmovl ", regName, ", (", setName, ")");
	dlinkAppend(instList,dlinkNodeAlloc(inst));
	freeIntegerRegister((int)SymGetFieldByIndex(rsymtab,rhsRegIndex,SYMTAB_REGISTER_INDEX_FIELD));
	if (test) {
		freeIntegerRegister((int)SymGetFieldByIndex(rsymtab,lhsRegIndex,SYMTAB_REGISTER_INDEX_FIELD));
	} else {
		freeIntegerRegister((int)SymGetFieldByIndex(lsymtab,lhsRegIndex,SYMTAB_REGISTER_INDEX_FIELD));
	}
}

/**
 * Add the instructions needed to read a variable using the read system call.
 *
 * @param instList a DList of instructions
 * @param symtab a symbol table
 * @param addrIndex the symbol table index of the register holding the address that is to be read into
 */
void emitReadVariable(DList instList, SymTable symtab, int addrIndex) {
	char *inst = nssave(3,"\tmovl $", READ_INTEGER_FMT, ", %edi");
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = nssave(3,"\tmovl ", (char*)SymGetFieldByIndex(symtab,addrIndex,SYM_NAME_FIELD), ", %esi");
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = ssave("\tmovl $0, %eax");
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = ssave("\tcall scanf");
	dlinkAppend(instList,dlinkNodeAlloc(inst));
	freeIntegerRegister((int)SymGetFieldByIndex(symtab,addrIndex,SYMTAB_REGISTER_INDEX_FIELD));
}

/**
 * Create a unique label
 * @param label a character array of size 20 in which the label will be stored
 */
static void makeLabel(char label[20]) {
	static int labelCount = 0;
	snprintf(label,19,".L%d",labelCount++);
}

/**
 * Insert instructions to test whether the expression of a if-statement is false, if false, branch around the then-part
 * of the if-statement.
 *
 * @param instList a list of instructions
 * @param symtab a symbol table
 * @param regIndex the symbol table index of the register holding the rest of the test expression of an if-statement
 * @return the symbol table index of the label that must follow the then-part of an if-statement
 */
int emitIfTest(DList instList, SymTable symtab, int regIndex) {
	char label[20];
	makeLabel(label);

	int treg = allocateIntegerRegister();
	char *symReg = getIntegerRegisterName(treg);
	int tregIndex = SymIndex(symtab,symReg);
	SymPutFieldByIndex(symtab,tregIndex,SYMTAB_REGISTER_INDEX_FIELD,(Generic)treg);

	char* inst = nssave(2,"\tmovl $-1, ", symReg);
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = nssave(4,"\ttestl ",(char*)SymGetFieldByIndex(symtab,regIndex,SYM_NAME_FIELD), ", ",symReg);
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	freeIntegerRegister((int)SymGetFieldByIndex(symtab,regIndex,SYMTAB_REGISTER_INDEX_FIELD));
	freeIntegerRegister(treg);

	inst = nssave(2,"\tje ",label); /* jump to false*/
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	return SymIndex(symtab,label);
}
/**
 * Insert a nop as a branch target in the list of instructions.
 *
 * @param instList a list of instructions
 * @param symtab a symbol table
 * @param endLabelIndex the symbol table index of the label for the nop
 */
void emitEndBranchTarget(DList instList, SymTable symtab, int endLabelIndex) {
	char* inst = nssave(2,SymGetFieldByIndex(symtab,endLabelIndex,SYM_NAME_FIELD),":\t nop");
	dlinkAppend(instList, dlinkNodeAlloc(inst));
}

/**
 * Insert a branch to an ending label after the else-part of an if-statement.
 *
 * @param instList a list of instructions
 * @param symtab a symbol table
 * @param elseLabelIndex the symbol table index of the label for the beginning of the else-part of an if-statement
 * @return a symbol table index for the end label of an if-statement
 */
int emitThenBranch(DList instList, SymTable symtab, int elseLabelIndex) {
	char label[20];
	makeLabel(label);

	char* inst = nssave(2,"\tjmp ",label);
	dlinkAppend(instList, dlinkNodeAlloc(inst));
	emitEndBranchTarget(instList,symtab,elseLabelIndex);

	return SymIndex(symtab,label);
}
/**
 * Insert a nop to serve as a target of the backwards branch of a while-statement
 *
 * @param instList a list of instructions
 * @param symtab a symbol table
 * @return the label for the backwards branch target
 */
int emitWhileLoopLandingPad(DList instList,SymTable symtab) {
	char label[20];
	makeLabel(label);

	char *inst = nssave(2,label,":\tnop");
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	return SymIndex(symtab,label);
}

/**
 * Insert a test to enter a while loop. If the test is false, branch to a label after the loop.
 *
 * @param instList a list of instructions
 * @param symtab a symbol table
 * @param regIndex a symbol table index for the register holding the result of the test expression of a while-statement
 * @return a symbol table index for the label at the end of the while-loop
 */
int emitWhileLoopTest(DList instList, SymTable symtab, int regIndex) {
	char label[20];
	makeLabel(label);

	int treg = allocateIntegerRegister();
	char *symReg = getIntegerRegisterName(treg);
	int tregIndex = SymIndex(symtab,symReg);
	SymPutFieldByIndex(symtab,tregIndex,SYMTAB_REGISTER_INDEX_FIELD,(Generic)treg);

	char* inst = nssave(2,"\tmovl $-1, ", symReg);
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = nssave(4,"\ttestl ",(char*)SymGetFieldByIndex(symtab,regIndex,SYM_NAME_FIELD), ", ",symReg);
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	freeIntegerRegister((int)SymGetFieldByIndex(symtab,regIndex,SYMTAB_REGISTER_INDEX_FIELD));
	freeIntegerRegister(treg);

	inst = nssave(2,"\tje ",label);
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	return SymIndex(symtab,label);
}

/**
 * Insert a branch back to the the landing pad of a while loop, followed by a branch target for loop exit.
 *
 * @param instList a list of instructions
 * @param symtab a symbol table
 * @param beginLabelIndex a symbol table index of the label for the while loop landing pad
 * @param endLabelIndex a symbol table index of the lable for the exit of the while loop
 */
void emitWhileLoopBackBranch(DList instList, SymTable symtab, int beginLabelIndex, int endLabelIndex) {
	char *inst = nssave(2,"\tjmp ",(char*)SymGetFieldByIndex(symtab,beginLabelIndex,SYM_NAME_FIELD));
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = nssave(2,(char*)SymGetFieldByIndex(symtab,endLabelIndex,SYM_NAME_FIELD),":\t nop");
	dlinkAppend(instList,dlinkNodeAlloc(inst));
}

/**
 * Add the instructions needed to write a value using the print system call.
 *
 * @param instList a Dlist of instructions
 * @param symtab a symbol table
 * @param regIndex the symbol table index of the register to be printed (must be addres if string)
 * @param syscallService the system call print service to use (format string for x86)
 */
void emitWriteExpression(DList instList,SymTable symtab, int regIndex, char *syscallService) {
	char *inst = nssave(3,"\tmovl ", (char*)SymGetFieldByIndex(symtab,regIndex,SYM_NAME_FIELD), ", %esi");
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = ssave("\tmovl $0, %eax");
	dlinkAppend(instList,dlinkNodeAlloc(inst));
	freeIntegerRegister((int)SymGetFieldByIndex(symtab,regIndex,SYMTAB_REGISTER_INDEX_FIELD));

	inst = nssave(3, "\tmovl $",syscallService, ", %edi");
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = ssave("\tcall printf");
	dlinkAppend(instList,dlinkNodeAlloc(inst));
}

/**
 * Add an instruction that performs a binary computation.
 *
 * @param instList a DList of instructions
 * @param symtab a symbol table
 * @param leftOperand the symbol table index of the register holding the left operand
 * @param rightOperand the symbol table index of the register holding the right operand
 * @param opcode the opcode of the mips assembly instruction
 * @return
 */
static int emitBinaryExpression(DList instList, SymTable symtab, int leftOperand, int rightOperand, char* opcode) {
	char* leftName = (char*)SymGetFieldByIndex(symtab,leftOperand,SYM_NAME_FIELD);
	char* rightName = (char*)SymGetFieldByIndex(symtab,rightOperand,SYM_NAME_FIELD);

	char* inst = nssave(6,"\t",opcode," ", rightName,", ",leftName);
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	freeIntegerRegister((int)SymGetFieldByIndex(symtab,rightOperand,SYMTAB_REGISTER_INDEX_FIELD));
	return leftOperand;
}

/**
 * Add an or instruction.
 *
 * @param instList a DList of instructions
 * @param symtab a symbol table
 * @param leftOperand the symbol table index of the register holding the left operand
 * @param rightOperand the symbol table index of the register holding the right operand
 * @return the symbol table index for the result register
 */
int emitOrExpression(DList instList, SymTable symtab, int leftOperand, int rightOperand) {
	return emitBinaryExpression(instList,symtab,leftOperand,rightOperand,"orl");
}

/**
 * Add an and instruction.
 *
 * @param instList a DList of instructions
 * @param symtab a symbol table
 * @param leftOperand the symbol table index of the register holding the left operand
 * @param rightOperand the symbol table index of the register holding the right operand
 * @return the symbol table index for the result register
 */
int emitAndExpression(DList instList, SymTable symtab, int leftOperand, int rightOperand) {
	return emitBinaryExpression(instList,symtab,leftOperand,rightOperand,"andl");
}

/**
 * Add a not instruction.
 *
 * @param instList a DList of instructions
 * @param symtab a symbol table
 * @param operand the symbol table index of the register holding the operand
 * @return the symbol table index for the result register
 */
int emitNotExpression(DList instList, SymTable symtab, int operand) {
	char* opName = (char*)SymGetFieldByIndex(symtab,operand,SYM_NAME_FIELD);
	char* inst = nssave(2, "\txorl $1, ", opName);
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	return operand;
}

static int emitBinaryCompareExpression(DList instList, SymTable symtab, int leftOperand, int rightOperand, char *opcode) {
	leftOperand = emitBinaryExpression(instList,symtab,leftOperand,rightOperand,"cmpl");
	freeIntegerRegister((int)SymGetFieldByIndex(symtab,rightOperand,SYMTAB_REGISTER_INDEX_FIELD));

	char *inst = nssave(2,"\tmovl $0, ", (char*)SymGetFieldByIndex(symtab,leftOperand,SYM_NAME_FIELD));
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	int tregIndex = getFreeIntegerRegisterIndex(symtab);

	inst = nssave(2,"\tmovl $1, ",(char*)SymGetFieldByIndex(symtab,tregIndex,SYM_NAME_FIELD));
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	return emitBinaryExpression(instList,symtab,leftOperand,tregIndex,opcode);
}

/**
 * Add an equal instruction.
 *
 * @param instList a DList of instructions
 * @param symtab a symbol table
 * @param leftOperand the symbol table index of the register holding the left operand
 * @param rightOperand the symbol table index of the register holding the right operand
 * @return the symbol table index for the result register
 */
int emitEqualExpression(DList instList, SymTable symtab, int leftOperand, int rightOperand) {
    return emitBinaryCompareExpression(instList,symtab,leftOperand,rightOperand,"cmove");
}
/**
 * Add a not-equal instruction.
 *
 * @param instList a DList of instructions
 * @param symtab a symbol table
 * @param leftOperand the symbol table index of the register holding the left operand
 * @param rightOperand the symbol table index of the register holding the right operand
 * @return the symbol table index for the result register
 */

int emitNotEqualExpression(DList instList, SymTable symtab, int leftOperand, int rightOperand) {
	return emitBinaryCompareExpression(instList,symtab,leftOperand,rightOperand,"cmovne");
}

/**
 * Add an less-or-equal instruction.
 *
 * @param instList a DList of instructions
 * @param symtab a symbol table
 * @param leftOperand the symbol table index of the register holding the left operand
 * @param rightOperand the symbol table index of the register holding the right operand
 * @return the symbol table index for the result register
 */
int emitLessEqualExpression(DList instList, SymTable symtab, int leftOperand, int rightOperand) {
	return emitBinaryCompareExpression(instList,symtab,leftOperand,rightOperand,"cmovle");
}

/**
 * Add a less-than instruction.
 *
 * @param instList a DList of instructions
 * @param symtab a symbol table
 * @param leftOperand the symbol table index of the register holding the left operand
 * @param rightOperand the symbol table index of the register holding the right operand
 * @return the symbol table index for the result register
 */
int emitLessThanExpression(DList instList, SymTable symtab, int leftOperand, int rightOperand) {
	return emitBinaryCompareExpression(instList,symtab,leftOperand,rightOperand,"cmovl");
}

/**
 * Add a greater-equal instruction.
 *
 * @param instList a DList of instructions
 * @param symtab a symbol table
 * @param leftOperand the symbol table index of the register holding the left operand
 * @param rightOperand the symbol table index of the register holding the right operand
 * @return the symbol table index for the result register
 */
int emitGreaterEqualExpression(DList instList, SymTable symtab, int leftOperand, int rightOperand) {
	return emitBinaryCompareExpression(instList,symtab,leftOperand,rightOperand,"cmovge");
}

/**
 * Add a greater-than instruction.
 *
 * @param instList a DList of instructions
 * @param symtab a symbol table
 * @param leftOperand the symbol table index of the register holding the left operand
 * @param rightOperand the symbol table index of the register holding the right operand
 * @return the symbol table index for the result register
 */
int emitGreaterThanExpression(DList instList, SymTable symtab, int leftOperand, int rightOperand) {
	return emitBinaryCompareExpression(instList,symtab,leftOperand,rightOperand,"cmovg");
}


/**
 * Add an add instruction.
 *
 * @param instList a DList of instructions
 * @param symtab a symbol table
 * @param leftOperand the symbol table index of the register holding the left operand
 * @param rightOperand the symbol table index of the register holding the right operand
 * @return the symbol table index for the result register
 */
int emitAddExpression(DList instList, SymTable symtab, int leftOperand, int rightOperand) {
	return emitBinaryExpression(instList,symtab,leftOperand,rightOperand,"addl");
}

/**
 * Add a subtract instruction.
 *
 * @param instList a DList of instructions
 * @param symtab a symbol table
 * @param leftOperand the symbol table index of the register holding the left operand
 * @param rightOperand the symbol table index of the register holding the right operand
 * @return the symbol table index for the result register
 */
int emitSubtractExpression(DList instList, SymTable symtab, int leftOperand, int rightOperand) {
	return emitBinaryExpression(instList,symtab,leftOperand,rightOperand,"subl");
}

/**
 * Add a multiply instruction.
 *
 * @param instList a DList of instructions
 * @param symtab a symbol table
 * @param leftOperand the symbol table index of the register holding the left operand
 * @param rightOperand the symbol table index of the register holding the right operand
 * @return the symbol table index for the result register
 */
int emitMultiplyExpression(DList instList, SymTable symtab, int leftOperand, int rightOperand) {
	return emitBinaryExpression(instList,symtab,leftOperand,rightOperand,"imull");
}

/**
 * Add a divide instruction.
 *
 * @param instList a DList of instructions
 * @param symtab a symbol table
 * @param leftOperand the symbol table index of the register holding the left operand
 * @param rightOperand the symbol table index of the register holding the right operand
 * @return the symbol table index for the result register
 */
int emitDivideExpression(DList instList, SymTable symtab, int leftOperand, int rightOperand) {
	int leftReg = (int)SymGetFieldByIndex(symtab,leftOperand,SYMTAB_REGISTER_INDEX_FIELD);
	int rightReg = (int)SymGetFieldByIndex(symtab,rightOperand,SYMTAB_REGISTER_INDEX_FIELD);
	char *inst = nssave(3,"\tmovl ",(char*)SymGetFieldByIndex(symtab,leftOperand,SYM_NAME_FIELD), ", %eax");
    dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = ssave("\tcdq");
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = nssave(2,"\tidivl ",(char*)SymGetFieldByIndex(symtab,rightOperand,SYM_NAME_FIELD));
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = nssave(2,"\tmovl %eax, ", (char *)SymGetFieldByIndex(symtab, leftOperand, SYM_NAME_FIELD)); 
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	freeIntegerRegister(rightReg);
	return leftOperand;
}

/**
 * Add an instruction to compute the address of a variable.
 *
 * @param instList a Dlist of instructions
 * @param lsymtab a global symbol table
 * @param symtab a symbol table
 * @param varIndex the symbol table index for a variable
 * @return the symbol table index of the result register
 */
int emitComputeVarAddress(DList instList, SymTable lsymtab, SymTable symtab, char* varName) {
	int regIndex = getFreeIntegerRegisterIndex(symtab);
	char* regName = (char*)get64bitIntegerRegisterName(symtab, regIndex);

	int offset = 0;
	int varIndex = SymQueryIndex(symtab,varName);
	if (varIndex == SYM_INVALID_INDEX) {
		varIndex = SymQueryIndex(lsymtab,varName);
		offset = (int)SymGetFieldByIndex(lsymtab,varIndex,SYMTAB_OFFSET_FIELD);
		char offsetStr[10];
		snprintf(offsetStr,9,"%d",offset);
		char *inst = nssave(2,"\tmovq $_gp,", regName);
		dlinkAppend(instList,dlinkNodeAlloc(inst));

		inst = nssave(4,"\taddq $", offsetStr, ", ", regName);
		dlinkAppend(instList,dlinkNodeAlloc(inst));

		return regIndex;
	} else {
		char *oldRegName = (char*)SymGetFieldByIndex(symtab,varIndex,SYM_NAME_FIELD);
		offset = (((int)SymGetFieldByIndex(symtab,varIndex,SYMTAB_OFFSET_FIELD) * -1) - 4);
		char offsetStr[10];
		snprintf(offsetStr,9,"%d",offset);
		char *inst = nssave(2,"\tmovq %rbp, ", regName);
		dlinkAppend(instList,dlinkNodeAlloc(inst));

		inst = nssave(4,"\taddq $", offsetStr, ", ", regName);
		dlinkAppend(instList,dlinkNodeAlloc(inst));

		return regIndex;
	}
}

/**
 * Compute the address of an array element and store it in a register.
 *
 * @param instList a list of instructions
 * @param gsymtab global symbol table
 * @param symtab a symbol table
 * @param varIndex the symbol table index of the array variable
 * @param subIndex the symbol table index of the register holding the subscript value
 * @return the symbol table index of the register holding the address of the
 * 		   array element.
 */
int emitComputeArrayAddress(DList instList, SymTable gsymtab, SymTable symtab, char *varName, int subIndex) {
	int regIndex = getFreeIntegerRegisterIndex(symtab);
	char* regName = get64bitIntegerRegisterName(symtab, regIndex);

	char *inst;
	int offset = 0;

	/* Checks to see if var index is in the local table otherwise it grabs the address of the global */
	int varIndex = SymQueryIndex(symtab,varName);
	if (varIndex == SYM_INVALID_INDEX) {
		varIndex = SymQueryIndex(gsymtab,varName);
		int varTypeIndex = (int)SymGetFieldByIndex(gsymtab,varIndex,SYMTAB_TYPE_INDEX_FIELD);
		if (isArrayType(gsymtab,varTypeIndex)) {
			offset = (int)SymGetFieldByIndex(gsymtab,varIndex,SYMTAB_OFFSET_FIELD);
			char offsetStr[10];
			snprintf(offsetStr,9,"%d",offset);

			inst = nssave(2,"\tmovq $_gp, ", regName);
			dlinkAppend(instList,dlinkNodeAlloc(inst));

			inst = nssave(4,"\taddq $", offsetStr, ", ", regName);
			dlinkAppend(instList,dlinkNodeAlloc(inst));

			/* compute offset based on subscript */
		    char* subReg32Name = (char*)SymGetFieldByIndex(symtab,subIndex,SYM_NAME_FIELD);
			char* subRegName = get64bitIntegerRegisterName(symtab,subIndex);

			inst = nssave(4,"\tmovslq ", subReg32Name, ", ", subRegName);
			dlinkAppend(instList,dlinkNodeAlloc(inst));

			inst = nssave(2,"\timulq $4, ", subRegName);
			dlinkAppend(instList,dlinkNodeAlloc(inst));

			/* compute element address */
			inst = nssave(4,"\taddq ", subRegName, ", ", regName);
			dlinkAppend(instList,dlinkNodeAlloc(inst));
		} else {
			char msg[80];
			snprintf(msg,80,"Scalar variable %s used as an array", (char*)SymGetFieldByIndex(gsymtab,varIndex,SYM_NAME_FIELD));
			Cminus_error(msg);
		}
	} else {
		/* Grabs the local address by generating the offset */
		int varTypeIndex = (int)SymGetFieldByIndex(symtab,varIndex,SYMTAB_TYPE_INDEX_FIELD);
		if (isArrayType(symtab,varTypeIndex)) {
			offset = (((int)SymGetFieldByIndex(symtab,varIndex,SYMTAB_OFFSET_FIELD) * -1) - 4);
			char offsetStr[10];
			snprintf(offsetStr,9,"%d",offset);

			inst = nssave(2,"\tmovq %rbp, ",regName);
			dlinkAppend(instList,dlinkNodeAlloc(inst));

			inst = nssave(4,"\taddq $", offsetStr, ", ", regName);
			dlinkAppend(instList,dlinkNodeAlloc(inst));

			/* compute offset based on subscript */
		    char* subReg32Name = (char*)SymGetFieldByIndex(symtab,subIndex,SYM_NAME_FIELD);
			char* subRegName = get64bitIntegerRegisterName(symtab, subIndex);

			inst = nssave(4,"\tmovslq ", subReg32Name, ", ", subRegName);
			dlinkAppend(instList,dlinkNodeAlloc(inst));

			inst = nssave(2,"\timulq $-4, ", subRegName);
			dlinkAppend(instList,dlinkNodeAlloc(inst));

			/* compute element address */
			inst = nssave(4,"\taddq ", subRegName, ", ", regName);
			dlinkAppend(instList,dlinkNodeAlloc(inst));
		} else {
			char msg[80];
			snprintf(msg,80,"Scalar variable %s used as an array", (char*)SymGetFieldByIndex(symtab,varIndex,SYM_NAME_FIELD));
			Cminus_error(msg);
		}
	}

	freeIntegerRegister((int)SymGetFieldByIndex(symtab,subIndex,SYMTAB_REGISTER_INDEX_FIELD));
	return regIndex;
}

/**
 * Add an instruction to load a variable from memory.
 *
 * @param instList a Dlist of instructions
 * @param lsymtab a global symbol table
 * @param symtab a symbol table
 * @param regIndex the symbol table index for the address of a variable
 * @return the symbol table index of the result register
 */
int emitLoadVariable(DList instList, SymTable lsymtab, SymTable symtab, int regIndex) {
	int newRegIndex = getFreeIntegerRegisterIndex(symtab);
	char* newRegName = (char*)SymGetFieldByIndex(symtab,newRegIndex,SYM_NAME_FIELD);
	char* regName = (char*)get64bitIntegerRegisterName(symtab, regIndex);

	if (regName == NULL) {
		regName = (char*)get64bitIntegerRegisterName(lsymtab, regIndex);
	}

	char *inst = nssave(4,"\tmovl (",regName,"), ", newRegName);
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	freeIntegerRegister((int)SymGetFieldByIndex(symtab,regIndex,SYMTAB_REGISTER_INDEX_FIELD));
	return newRegIndex;
}

/**
 * Add an instruction to load an integer constant
 *
 * @param instList a Dlist of instructions
 * @param symtab a symbol table
 * @param intIndex the symbol table index for an integer constant
 * @return the symbol table index of the result register
 */
int emitLoadIntegerConstant(DList instList, SymTable symtab, int intIndex) {
	int regIndex = getFreeIntegerRegisterIndex(symtab);
	char* regName = (char*)SymGetFieldByIndex(symtab,regIndex,SYM_NAME_FIELD);
	
	char *intName = SymGetFieldByIndex(symtab,intIndex,SYM_NAME_FIELD);
	char *inst = nssave(4,"\tmovl $", intName, ", ", regName);
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	return regIndex;
}

/**
 * Starts each function by pushing necessary registers onto the stack
 * Also figures out the correct starting offset of the stack
 *
 * @param instList a Dlist of instructions
 * @param offset is the total byte offset that needs to be aligned
 */
void emitStartFunction(DList instList, int offset) {
	/* Generates the necessary offset that is 16 byte aligned */
	int newOffset = offset + (16 - (offset % 16));
	char offsetStr[10];
	snprintf(offsetStr,9,"%d",offset);

	char *inst = nssave(3, "\tsubq $", offsetStr, ", %rsp");
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = ssave("\tpushq %rbx");
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = ssave("\tpushq %r12");
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = ssave("\tpushq %r13");
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = ssave("\tpushq %r14");
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = ssave("\tpushq %r15");
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = ssave("\tsubq $8, %rsp");
	dlinkAppend(instList,dlinkNodeAlloc(inst));
}

/**
 * Calls a defined function by name
 *
 * @param instList a Dlist of instructions
 * @param symtab a symbol table
 * @param func the name of the function to be called
 * @return the symbol table index of the result register
 */
int emitCallFunction(DList instList, SymTable symtab, char *func) {
	int newRegIndex = getFreeIntegerRegisterIndex(symtab);
	char* newRegName = (char*)SymGetFieldByIndex(symtab,newRegIndex,SYM_NAME_FIELD);
	char *inst;
	
	inst = nssave(2,"\tcall ",func);
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = nssave(2,"\tmovl %eax, ",newRegName);
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	return newRegIndex;
}

/**
 * Compute the address of an array element and store it in a register.
 *
 * @param instList a list of instructions
 * @param lsymtab global symbol table
 * @param symtab a symbol table
 * @param funcIndec the index of the return register storing the final value
 */
void emitReturnFunction(DList instList, SymTable lsymtab, SymTable symtab, int funcIndex) {
	int test = 1;
	char *regName = (char*)SymGetFieldByIndex(symtab,funcIndex,SYM_NAME_FIELD);
	if (regName == NULL) {
		test = 0;
		regName = (char*)SymGetFieldByIndex(lsymtab,funcIndex,SYM_NAME_FIELD);
	}

	char *inst = nssave(3,"\tmovl ",regName,", %eax");
	dlinkAppend(instList,dlinkNodeAlloc(inst));
	if (test) {
		freeIntegerRegister((int)SymGetFieldByIndex(symtab,funcIndex,SYMTAB_REGISTER_INDEX_FIELD));
	} else {
		freeIntegerRegister((int)SymGetFieldByIndex(lsymtab,funcIndex,SYMTAB_REGISTER_INDEX_FIELD));
	}
}

/**
 * Ends each function by popping necessary registers off the stack
 *
 * @param instList a Dlist of instructions
 */
void emitEndFunction(DList instList) {
	char *inst = ssave("\taddq $8, %rsp");
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = ssave("\tpopq %r15");
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = ssave("\tpopq %r14");
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = ssave("\tpopq %r13");
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = ssave("\tpopq %r12");
	dlinkAppend(instList,dlinkNodeAlloc(inst));

	inst = ssave("\tpopq %rbx");
	dlinkAppend(instList,dlinkNodeAlloc(inst));
}

/**
 * Just a test function to print out instructions mid code
 * 
 * @param instList a Dlist of instructions
 * @param test is a char array of string to be printed
 */
void emitTest(DList instList, char *test) {
	char *inst;
	inst = nssave(2,"\t",test);
	dlinkAppend(instList,dlinkNodeAlloc(inst));
}

/**
 * Add a .asciiz declaration for a string constant.
 *
 * @param dataList a DList of data declarations
 * @param symtab a symbol table
 * @param stringIndex the symbol table index of a string constant
 * @return
 */
static char* makeDataDeclaration(DList dataList, SymTable symtab, int stringIndex) {
	static int stringNum = 0;
	char* string = (char*)SymGetFieldByIndex(symtab,stringIndex,SYM_NAME_FIELD);
	char* strLabel = (char*)malloc(sizeof(char)*15);
	snprintf(strLabel,15,".string_const%d",stringNum++);

	char* strChars = substr(string,1,strlen(string)-2); /**< the string constant w/o quotes */
	char* decl = nssave(4,strLabel,": .string \"",strChars,"\"");
	dlinkAppend(dataList,dlinkNodeAlloc(decl));
	free(strChars);

	return strLabel;
}

/**
 * Add an instruction to load the address of a string constant
 *
 * @param instList a Dlist of instructions
 * @param dataList a Dlist of data declarations
 * @param symtab a symbol table
 * @param stringIndex the symbol table index for a string constant
 * @return the symbol table index of the result register
 */
int emitLoadStringConstantAddress(DList instList, DList dataList, SymTable symtab, int stringIndex) {
	char *strLabel = makeDataDeclaration(dataList,symtab,stringIndex);
	int regIndex = getFreeIntegerRegisterIndex(symtab);
	char* regName = (char*)SymGetFieldByIndex(symtab,regIndex,SYM_NAME_FIELD);

	char* inst = nssave(4,"\tmovl $", strLabel, ", ", regName);
	dlinkAppend(instList,dlinkNodeAlloc(inst));
	free(strLabel);

	return regIndex;
}

/**
 * Add an identifier to the symbol table and store its offset 
 * This function is called by dlinkApply1.
 *
 * @param node a node on a linked list containing the symbol table index of a variable
 * 		  delcared in a program
 * @param data a structure containing the symbol table index of the type of the variable,
 * 		  the symbol table, and the current offset in the activation record.
 */
void addIdToSymtab(DNode node, AddIdStructPtr data) {
	int symIndex = (int)dlinkNodeAtom(node);
	int typeIndex = (int)SymGetFieldByIndex(data->symtab,symIndex,SYMTAB_TYPE_INDEX_FIELD);
	
	if (typeIndex == -1) {
		SymPutFieldByIndex(data->symtab,symIndex,SYMTAB_TYPE_INDEX_FIELD,(Generic)data->typeIndex);
		typeIndex = data->typeIndex;
	}

    int size = (int)SymGetFieldByIndex(data->symtab,typeIndex,SYMTAB_SIZE_FIELD);
    SymPutFieldByIndex(data->symtab,symIndex,SYMTAB_OFFSET_FIELD,(Generic)(data->offset));
    data->offset += size;
}

/**
 *  * Return true if a type is an array, false otherwise.
 *   *
 *    * @param symtab a symbol table
 *     * @param typeIndex a symbol table index for a type
 *      * @return see above
 *       */
bool isArrayType(SymTable symtab, int typeIndex) {
    char *typeString = SymGetFieldByIndex(symtab,typeIndex,SYM_NAME_FIELD);
    return (bool)(strchr(typeString,'[') != NULL);
}

