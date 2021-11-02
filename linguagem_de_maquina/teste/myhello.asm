section .data
    myhello db "Ola mundo!",10
    tam equ $ - myhello 
    myhello1 db 15       ;quero mover o endereco de myhello para myhello1

section .text
    global _start
    _start:

    mov rax, 4
    mov rbx, 1
    mov rcx, myhello
    mov rdx, tam
    int 0x80
    mov rax,1
    mov rbx,1
    int 0X80
