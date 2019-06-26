section .data
    Msg: db 'tarfao',0
    tamMsg: equ $ -  Msg

    MsgInver: times 10 db 0


section .text
    global _start
    _start:

    mov rbx, Msg
    mov di, [tamMsg]
    xor cx,cx

Invert:
    mov [MsgInver], [rbx + di]
    dec di	         ;decrementa o ax para ir para a próxima letra do final para o início
    add MsgInver,1   ;incrementa o si para ir para a próxima letra do início para o final
    cmp di,0 
    jnz Invert

    mov rax,1
    mov rbx,0
    int 0x80
    
