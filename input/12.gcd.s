	.section	.rodata
	.int_wformat: .string "%d\n"
	.float_wformat: .string "%f\n"
	.str_wformat: .string "%s\n"
	.int_rformat: .string "%d"
	.float_rformat: .string "%f"
	.comm _gp, 8, 4
.string_const0: .string "enter x:"
.string_const1: .string "enter y:"
.string_const2: .string "enter x:"
.string_const3: .string "enter y:"
	.text
	.globl gcd
	.type gcd,@function
gcd:	nop
	pushq %rbp
	movq %rsp, %rbp
	subq $4, %rsp
	pushq %rbx
	pushq %r12
	pushq %r13
	pushq %r14
	pushq %r15
	subq $8, %rsp
	movq $_gp,%rbx
	addq $4, %rbx
	movl (%rbx), %ecx
	movl $0, %ebx
	cmpl %ebx, %ecx
	movl $0, %ecx
	movl $1, %ebx
	cmove %ebx, %ecx
	movl $-1, %ebx
	testl %ecx, %ebx
	je .L0
	movq $_gp,%rbx
	addq $0, %rbx
	movl (%rbx), %ecx
	movl %ecx, %eax
	jmp .L1
.L0:	 nop
	movq %rbp, %rbx
	addq $-4, %rbx
	movq $_gp,%rcx
	addq $0, %rcx
	movl (%rcx), %r8d
	movl %r8d, (%rbx)
	movq $_gp,%rbx
	addq $0, %rbx
	movq $_gp,%rcx
	addq $4, %rcx
	movl (%rcx), %r8d
	movl %r8d, (%rbx)
	movq $_gp,%rbx
	addq $4, %rbx
	movq %rbp, %rcx
	addq $-4, %rcx
	movl (%rcx), %r8d
	movq $_gp,%rcx
	addq $4, %rcx
	movl (%rcx), %r9d
	movq %rbp, %rcx
	addq $-4, %rcx
	movl (%rcx), %r10d
	movq $_gp,%rcx
	addq $4, %rcx
	movl (%rcx), %r11d
	movl %r10d, %eax
	cdq
	idivl %r11d
	movl %eax, %r10d
	imull %r10d, %r9d
	subl %r9d, %r8d
	movl %r8d, (%rbx)
	call gcd
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
	movl $.string_const0, %ebx
	movl %ebx, %esi
	movl $0, %eax
	movl $.str_wformat, %edi
	call printf
	movq $_gp,%rbx
	addq $0, %rbx
	movl $.int_rformat, %edi
	movl %ebx, %esi
	movl $0, %eax
	call scanf
	movl $.string_const1, %ebx
	movl %ebx, %esi
	movl $0, %eax
	movl $.str_wformat, %edi
	call printf
	movq $_gp,%rbx
	addq $4, %rbx
	movl $.int_rformat, %edi
	movl %ebx, %esi
	movl $0, %eax
	call scanf
.L2:	nop
	movq $_gp,%rbx
	addq $0, %rbx
	movl (%rbx), %ecx
	movl $0, %ebx
	cmpl %ebx, %ecx
	movl $0, %ecx
	movl $1, %ebx
	cmovne %ebx, %ecx
	movq $_gp,%rbx
	addq $4, %rbx
	movl (%rbx), %r8d
	movl $0, %ebx
	cmpl %ebx, %r8d
	movl $0, %r8d
	movl $1, %ebx
	cmovne %ebx, %r8d
	orl %r8d, %ecx
	movl $-1, %ebx
	testl %ecx, %ebx
	je .L3
	call gcd
	movl %eax, %ebx
	movl %ebx, %esi
	movl $0, %eax
	movl $.int_wformat, %edi
	call printf
	movl $.string_const2, %ebx
	movl %ebx, %esi
	movl $0, %eax
	movl $.str_wformat, %edi
	call printf
	movq $_gp,%rbx
	addq $0, %rbx
	movl $.int_rformat, %edi
	movl %ebx, %esi
	movl $0, %eax
	call scanf
	movl $.string_const3, %ebx
	movl %ebx, %esi
	movl $0, %eax
	movl $.str_wformat, %edi
	call printf
	movq $_gp,%rbx
	addq $4, %rbx
	movl $.int_rformat, %edi
	movl %ebx, %esi
	movl $0, %eax
	call scanf
	jmp .L2
.L3:	 nop
	addq $8, %rsp
	popq %r15
	popq %r14
	popq %r13
	popq %r12
	popq %rbx
	leave
	ret
