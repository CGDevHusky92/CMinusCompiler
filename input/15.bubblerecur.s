	.section	.rodata
	.int_wformat: .string "%d\n"
	.float_wformat: .string "%f\n"
	.str_wformat: .string "%s\n"
	.int_rformat: .string "%d"
	.float_rformat: .string "%f"
	.comm _gp, 52, 4
.string_const0: .string "Enter a[0:9]"
.string_const1: .string "After input"
.string_const2: .string "After sorting"
	.text
	.globl sort
	.type sort,@function
sort:	nop
	pushq %rbp
	movq %rsp, %rbp
	subq $16, %rsp
	pushq %rbx
	pushq %r12
	pushq %r13
	pushq %r14
	pushq %r15
	subq $8, %rsp
	movq $_gp,%rbx
	addq $44, %rbx
	movl (%rbx), %ecx
	movq $_gp,%rbx
	addq $48, %rbx
	movl (%rbx), %r8d
	cmpl %r8d, %ecx
	movl $0, %ecx
	movl $1, %ebx
	cmove %ebx, %ecx
	movl $-1, %ebx
	testl %ecx, %ebx
	je .L0
	movl $1, %ebx
	movl %ebx, %eax
	jmp .L1
.L0:	 nop
	movq %rbp, %rbx
	addq $-4, %rbx
	movq $_gp,%rcx
	addq $44, %rcx
	movl (%rcx), %r8d
	movl %r8d, (%rbx)
	movq %rbp, %rbx
	addq $-16, %rbx
	movq %rbp, %rcx
	addq $-4, %rcx
	movl (%rcx), %r8d
	movl %r8d, (%rbx)
	movq %rbp, %rbx
	addq $-8, %rbx
	movq $_gp,%rcx
	addq $44, %rcx
	movl (%rcx), %r8d
	movl $1, %ecx
	addl %ecx, %r8d
	movl %r8d, (%rbx)
.L2:	nop
	movq %rbp, %rbx
	addq $-8, %rbx
	movl (%rbx), %ecx
	movq $_gp,%rbx
	addq $48, %rbx
	movl (%rbx), %r8d
	cmpl %r8d, %ecx
	movl $0, %ecx
	movl $1, %ebx
	cmovle %ebx, %ecx
	movl $-1, %ebx
	testl %ecx, %ebx
	je .L3
	movq %rbp, %rbx
	addq $-8, %rbx
	movl (%rbx), %ecx
	movq $_gp, %rbx
	addq $0, %rbx
	movslq %ecx, %rcx
	imulq $4, %rcx
	addq %rcx, %rbx
	movl (%rbx), %ecx
	movq %rbp, %rbx
	addq $-16, %rbx
	movl (%rbx), %r8d
	movq $_gp, %rbx
	addq $0, %rbx
	movslq %r8d, %r8
	imulq $4, %r8
	addq %r8, %rbx
	movl (%rbx), %r8d
	cmpl %r8d, %ecx
	movl $0, %ecx
	movl $1, %ebx
	cmovl %ebx, %ecx
	movl $-1, %ebx
	testl %ecx, %ebx
	je .L4
	movq %rbp, %rbx
	addq $-16, %rbx
	movq %rbp, %rcx
	addq $-8, %rcx
	movl (%rcx), %r8d
	movl %r8d, (%rbx)
	jmp .L5
.L4:	 nop
.L5:	 nop
	movq %rbp, %rbx
	addq $-8, %rbx
	movq %rbp, %rcx
	addq $-8, %rcx
	movl (%rcx), %r8d
	movl $1, %ecx
	addl %ecx, %r8d
	movl %r8d, (%rbx)
	jmp .L2
.L3:	 nop
	movq %rbp, %rbx
	addq $-12, %rbx
	movq %rbp, %rcx
	addq $-4, %rcx
	movl (%rcx), %r8d
	movq $_gp, %rcx
	addq $0, %rcx
	movslq %r8d, %r8
	imulq $4, %r8
	addq %r8, %rcx
	movl (%rcx), %r8d
	movl %r8d, (%rbx)
	movq %rbp, %rbx
	addq $-4, %rbx
	movl (%rbx), %ecx
	movq $_gp, %rbx
	addq $0, %rbx
	movslq %ecx, %rcx
	imulq $4, %rcx
	addq %rcx, %rbx
	movq %rbp, %rcx
	addq $-16, %rcx
	movl (%rcx), %r8d
	movq $_gp, %rcx
	addq $0, %rcx
	movslq %r8d, %r8
	imulq $4, %r8
	addq %r8, %rcx
	movl (%rcx), %r8d
	movl %r8d, (%rbx)
	movq %rbp, %rbx
	addq $-16, %rbx
	movl (%rbx), %ecx
	movq $_gp, %rbx
	addq $0, %rbx
	movslq %ecx, %rcx
	imulq $4, %rcx
	addq %rcx, %rbx
	movq %rbp, %rcx
	addq $-12, %rcx
	movl (%rcx), %r8d
	movl %r8d, (%rbx)
	movq %rbp, %rbx
	addq $-4, %rbx
	movq %rbp, %rcx
	addq $-4, %rcx
	movl (%rcx), %r8d
	movl $1, %ecx
	addl %ecx, %r8d
	movl %r8d, (%rbx)
	movq $_gp,%rbx
	addq $44, %rbx
	movq $_gp,%rcx
	addq $44, %rcx
	movl (%rcx), %r8d
	movl $1, %ecx
	addl %ecx, %r8d
	movl %r8d, (%rbx)
	call sort
	movl %eax, %ebx
	movl %ebx, %eax
.L1:	 nop
	addq $8, %rsp
	popq %r15
	popq %r14
	popq %r13
	popq %r12
	popq %rbx
	leave
	ret
	.globl output
	.type output,@function
output:	nop
	pushq %rbp
	movq %rsp, %rbp
	subq $4, %rsp
	pushq %rbx
	pushq %r12
	pushq %r13
	pushq %r14
	pushq %r15
	subq $8, %rsp
	movq %rbp, %rbx
	addq $-4, %rbx
	movl $0, %ecx
	movl %ecx, (%rbx)
.L6:	nop
	movq %rbp, %rbx
	addq $-4, %rbx
	movl (%rbx), %ecx
	movl $10, %ebx
	cmpl %ebx, %ecx
	movl $0, %ecx
	movl $1, %ebx
	cmovl %ebx, %ecx
	movl $-1, %ebx
	testl %ecx, %ebx
	je .L7
	movq %rbp, %rbx
	addq $-4, %rbx
	movl (%rbx), %ecx
	movq $_gp, %rbx
	addq $0, %rbx
	movslq %ecx, %rcx
	imulq $4, %rcx
	addq %rcx, %rbx
	movl (%rbx), %ecx
	movl %ecx, %esi
	movl $0, %eax
	movl $.int_wformat, %edi
	call printf
	movq %rbp, %rbx
	addq $-4, %rbx
	movq %rbp, %rcx
	addq $-4, %rcx
	movl (%rcx), %r8d
	movl $1, %ecx
	addl %ecx, %r8d
	movl %r8d, (%rbx)
	jmp .L6
.L7:	 nop
	movq %rbp, %rbx
	addq $-4, %rbx
	movl (%rbx), %ecx
	movl %ecx, %eax
	addq $8, %rsp
	popq %r15
	popq %r14
	popq %r13
	popq %r12
	popq %rbx
	leave
	ret
	.globl input
	.type input,@function
input:	nop
	pushq %rbp
	movq %rsp, %rbp
	subq $4, %rsp
	pushq %rbx
	pushq %r12
	pushq %r13
	pushq %r14
	pushq %r15
	subq $8, %rsp
	movq %rbp, %rbx
	addq $-4, %rbx
	movl $0, %ecx
	movl %ecx, (%rbx)
	movl $.string_const0, %ebx
	movl %ebx, %esi
	movl $0, %eax
	movl $.str_wformat, %edi
	call printf
.L8:	nop
	movq %rbp, %rbx
	addq $-4, %rbx
	movl (%rbx), %ecx
	movl $10, %ebx
	cmpl %ebx, %ecx
	movl $0, %ecx
	movl $1, %ebx
	cmovl %ebx, %ecx
	movl $-1, %ebx
	testl %ecx, %ebx
	je .L9
	movq %rbp, %rbx
	addq $-4, %rbx
	movl (%rbx), %ecx
	movq $_gp, %rbx
	addq $0, %rbx
	movslq %ecx, %rcx
	imulq $4, %rcx
	addq %rcx, %rbx
	movl $.int_rformat, %edi
	movl %ebx, %esi
	movl $0, %eax
	call scanf
	movq %rbp, %rbx
	addq $-4, %rbx
	movq %rbp, %rcx
	addq $-4, %rcx
	movl (%rcx), %r8d
	movl $1, %ecx
	addl %ecx, %r8d
	movl %r8d, (%rbx)
	jmp .L8
.L9:	 nop
	movq %rbp, %rbx
	addq $-4, %rbx
	movl (%rbx), %ecx
	movl %ecx, %eax
	addq $8, %rsp
	popq %r15
	popq %r14
	popq %r13
	popq %r12
	popq %rbx
	leave
	ret
	.globl initialize
	.type initialize,@function
initialize:	nop
	pushq %rbp
	movq %rsp, %rbp
	subq $4, %rsp
	pushq %rbx
	pushq %r12
	pushq %r13
	pushq %r14
	pushq %r15
	subq $8, %rsp
	movq %rbp, %rbx
	addq $-4, %rbx
	movl $0, %ecx
	movl %ecx, (%rbx)
.L10:	nop
	movq %rbp, %rbx
	addq $-4, %rbx
	movl (%rbx), %ecx
	movl $20, %ebx
	cmpl %ebx, %ecx
	movl $0, %ecx
	movl $1, %ebx
	cmovl %ebx, %ecx
	movl $-1, %ebx
	testl %ecx, %ebx
	je .L11
	movq %rbp, %rbx
	addq $-4, %rbx
	movl (%rbx), %ecx
	movq $_gp, %rbx
	addq $0, %rbx
	movslq %ecx, %rcx
	imulq $4, %rcx
	addq %rcx, %rbx
	movl $0, %ecx
	movl %ecx, (%rbx)
	movq %rbp, %rbx
	addq $-4, %rbx
	movq %rbp, %rcx
	addq $-4, %rcx
	movl (%rcx), %r8d
	movl $1, %ecx
	addl %ecx, %r8d
	movl %r8d, (%rbx)
	jmp .L10
.L11:	 nop
	movl $1, %ebx
	movl %ebx, %eax
	addq $8, %rsp
	popq %r15
	popq %r14
	popq %r13
	popq %r12
	popq %rbx
	leave
	ret
	.globl main
	.type main,@function
main:	nop
	pushq %rbp
	movq %rsp, %rbp
	subq $0, %rsp
	pushq %rbx
	pushq %r12
	pushq %r13
	pushq %r14
	pushq %r15
	subq $8, %rsp
	movq $_gp,%rbx
	addq $40, %rbx
	call input
	movl %eax, %ecx
	movl %ecx, (%rbx)
	movl $.string_const1, %ebx
	movl %ebx, %esi
	movl $0, %eax
	movl $.str_wformat, %edi
	call printf
	movq $_gp,%rbx
	addq $40, %rbx
	call output
	movl %eax, %ecx
	movl %ecx, (%rbx)
	movq $_gp,%rbx
	addq $44, %rbx
	movl $0, %ecx
	movl %ecx, (%rbx)
	movq $_gp,%rbx
	addq $48, %rbx
	movl $9, %ecx
	movl %ecx, (%rbx)
	movq $_gp,%rbx
	addq $40, %rbx
	call sort
	movl %eax, %ecx
	movl %ecx, (%rbx)
	movl $.string_const2, %ebx
	movl %ebx, %esi
	movl $0, %eax
	movl $.str_wformat, %edi
	call printf
	movq $_gp,%rbx
	addq $40, %rbx
	call output
	movl %eax, %ecx
	movl %ecx, (%rbx)
	addq $8, %rsp
	popq %r15
	popq %r14
	popq %r13
	popq %r12
	popq %rbx
	leave
	ret
