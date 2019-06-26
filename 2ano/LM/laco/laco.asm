section .data
    Entre db 'Entre com um nome: '
    tamEntre equ $ - Entre
    Msg times 20 db 0
    tamMsg db 0;

%macro _printf 2
    ;-----------------------------------------------------------------------------------------------------------------------------------------------------
    ;o printf pode ser chamado de qualquer lugar do programa, e como ele utiliza os registradores ax,bx,cx e dx, iremos salvar oq há nele
    ;-----------------------------------------------------------------------------------------------------------------------------------------------------
    push rax
    push rbx
    push rcx
    push rdx
    ;-----------------------------------
    ;fazendo a execução do printf
    ;------------------------------------
    mov rax,4
    mov rbx,1
    mov rcx,%1
    mov rdx,%2
    ;-----------------------------------------------------------------------------------------------------------------------------------------------------
    ;depois que foi utilizado os registradores agora vamos colocar os antigos valores em seus respectivo registradores, que estão armazenados na pilha
    ;começa fazendo o rdx, pois como foi o último a ser armazenado na pilha, ele será o primeiro a sair
    ;-----------------------------------------------------------------------------------------------------------------------------------------------------
    int 0x80
    pop rdx
    pop rcx
    pop rbx
    pop rax
%endmacro

%macro _scanf 2
    ;como iremos utilizar o valor do rax fora da macro, não o salvamos
    push rbx
    push rcx
    push rdx
    mov rax,3
    mov rbx,0
    mov rcx,%1
    mov rdx,%2
    int 0x80
    pop rdx
    pop rcx
    pop rbx
%endmacro

section .text
    global _start

_start:

    _printf Entre,tamEntre
    _scanf Msg,20
    mov [tamMsg],rax
    
    mov rcx,10
    for10:
        ;---------------------------------------------------------------------------------------------------------------
        ;utilizamos o push e o pop aqui, caso não fizessemos isso na macro printf
        ;push rcx                ;salva o que ta em rcx, pois será mudado na macro printf, ele vai pra pilha agora
        ;---------------------------------------------------------------------------------------------------------------
        _printf Msg,[tamMsg]
        ;---------------------------------------------------------------------------------------------------------------
        ;pop rcx                 ;tira da pilha o que estava em rcx, e joga nele novamente
        ;---------------------------------------------------------------------------------------------------------------
        dec rcx
        jnz for10
    
    mov rax,1
    mov rbx,0
    int 0x80
