	.file	"lenum.c"
	.intel_syntax noprefix
	.section	.rodata
.LC0:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 48
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR [rbp-8], rax
	xor	eax, eax
	mov	rdx, QWORD PTR stdin[rip]
	lea	rax, [rbp-32]
	mov	esi, 10
	mov	rdi, rax
	call	fgets
	lea	rax, [rbp-32]
	mov	rdi, rax
	call	strlen
	mov	DWORD PTR [rbp-36], eax
	mov	DWORD PTR [rbp-40], 0
	mov	DWORD PTR [rbp-44], 0
	jmp	.L2
.L3:
	mov	edx, DWORD PTR [rbp-40]
	mov	eax, edx
	sal	eax, 2
	add	eax, edx
	add	eax, eax
	mov	edx, eax
	mov	eax, DWORD PTR [rbp-44]
	cdqe
	movzx	eax, BYTE PTR [rbp-32+rax]
	movsx	eax, al
	sub	eax, 48
	add	eax, edx
	mov	DWORD PTR [rbp-40], eax
	add	DWORD PTR [rbp-44], 1
.L2:
	mov	eax, DWORD PTR [rbp-36]
	sub	eax, 1
	cmp	eax, DWORD PTR [rbp-44]
	jg	.L3
	mov	eax, DWORD PTR [rbp-40]
	mov	esi, eax
	mov	edi, OFFSET FLAT:.LC0
	mov	eax, 0
	call	printf
	mov	eax, 0
	mov	rcx, QWORD PTR [rbp-8]
	xor	rcx, QWORD PTR fs:40
	je	.L5
	call	__stack_chk_fail
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
