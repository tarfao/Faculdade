%include "macro.inc"

section .data
	Msg db 'Entre com uma string com caracteres de 0 a 9: '
	tamMsg equ $ - Msg

	MsgConv db "Numero convertido é: "
	num db 0;
	strNum times 10 db 0
	tamStrNum db 0;

section .text
	global _start

	_start: 

	_printf Msg, tamMsg

	_scanf strNum,10

	;mov [tamStrNum],rax

	mov rcx,rax
	xor rsi,rsi
	xor rax, rax
	mov rbx,strNum

for:
	mul 10
	sub [rbx + rsi],'0'
	add rax, [rbx + rsi]
	inc rsi
	cmp rsi,rcx
	jl for

    mov [num],rax
    
    mov rax, 4
    mov rbx, 1
    mov rcx, num
    mov rdx, 1
    int 0x80
    
	mov eax,1
	mov ebx,0
	int 0x80
