section .data
    msg db 'Bem vindo, '    ;mensagem a ser exibida
    tamMsg equ $ - msg      ;tamanho da mensagem

    ler times 20 db 0               ;define 20 bytes para string
    tamLer db 0             ;define 1 byte com 0

%macro _printf 2
    mov rax,4
    mov rbx,1
    mov rcx,%1
    mov rdx,%2
    int 0x80
%endmacro

%macro _scanf 2
    mov rax,3
    mov rbx,0
    mov rcx,%1
    mov rdx,%2
    int 0x80
%endmacro

%macro _fim 0
    mov rax,1
    mov rbx,0
    int 0x80
%endmacro

section .text
    global _start
    _start:

    _scanf ler,20
    mov [tamLer],rax
    _printf msg,tamMsg
    _printf ler,[tamLer]
    _fim

   

   
