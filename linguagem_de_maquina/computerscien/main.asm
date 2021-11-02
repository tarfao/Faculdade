%include "macro.inc"
extern printf

section .data

	Msg: db "COMPUTER SCINECE IS THE BEST",0
	tamMsg: db 0

	Msg2: times 20 db 0
	tamMsg2: db 0

	format db "%d", 10, 0

section .text
	global main

main:
	
	push rbp

	mov rdi, format
	mov rsi, rax
	call printf

	pop rbp
	;_printf Msg,[tamMsg]

	_exit 0
	;xor rdx, rdx
	;xor rax, rax
