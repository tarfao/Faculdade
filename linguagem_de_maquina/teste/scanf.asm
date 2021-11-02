section .data
    inicia db 'Entre com seu nome: '
    tamInicia equ $ - inicia
    hello db 'Seja bem vindo, '
    tamHello equ $ - hello
    nome times 20 db 0
    tamNome db 0

section .text
    global _start
    _start:

    mov rax,4
    mov rbx,1
    mov rcx,inicia
    mov rdx,tamInicia
    int 0x80

    mov rax,3
    mov rbx,0
    mov rcx,nome
    mov rdx,20
    int 0x80
    mov [tamNome],rax

    mov rax,4
    mov rbx,1
    mov rcx,hello
    mov rdx,tamHello
    int 0x80

    mov rax,4
    mov rbx,1
    mov rcx,nome
    mov rdx,[tamNome]
    int 0x80
    

    mov rax,1
    mov rbx,10
    int 0x80 
