
%macro _printf 2    ;o numero 2 representa a quantidade de parametros
    push rax
    push rbx
    push rcx
    push rdx 

    mov rax,4
    mov rbx,1
    mov rcx,%1      ;representa o parametro 1 que é o buffer a ser gravado
    mov rdx,%2      ;representa o tamanho do buffer a ser gravado
    int 0x80

    pop rdx
    pop rcx
    pop rbx
    pop rax
%endmacro

%macro _scanf 2
    push rax
    push rbx 
    push rcx

    mov rax,3
    mov rbx,0
    mov rcx,%1
    mov rdx,%2
    int 0x80

    pop rcx
    pop rbx
    pop rax
%endmacro

%macro _exit 1
    mov rax, 1
    mov rbx, %1 
    int 0x80
%endmacro

%macro _gera_num1 2
    mov dl,10
    mul dl
    sub byte [%1 + %2], '0'
    add al, [%1 + %2]
%endmacro

