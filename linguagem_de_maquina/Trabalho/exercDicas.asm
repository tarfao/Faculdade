%include "/home/tafaum/Documentos/Faculdade/LM/Implementacoes/computerscien/macro.inc"
extern printf

section .data
   MENSAGEM: db 'COMPUTER SCIENC IS THE BEST',0   
   tamMENSAGEM: db 0
   fmt:    db "%d"
   msgCalculo db "O tamanho da mensagem é: "
   tamMsg db 0
   tamMsgCalc equ $-msgCalculo
 

section .text
   global _start
   _start:

   ;CALCULANDO O TAMANHO
   mov rdi, MENSAGEM
   xor al,al ;procura nulo = '\0'
   mov rcx, -1
   cld
   repnz scasb ; cx = - tamanho –2

   not rcx
   ; cx = tamanho + 1
   dec rcx
   _printf msgCalculo, tamMsgCalc
   mov [tamMsg],rcx

   _exit 0
   ;CHAMAR FUNCAO printf PARA IMPRIMIR O TAMANHO
   ;
   ;Passa os parâmetros e chama as funções C
   ;mov	rdi,fmt   ;1o parâmetro
   ;mov	rsi,tamMENSAGEM  ;2o parâmetro
   ;mov	rax,0
   ;call printf


   ;CRIAR UM ARQUIVO



   ;GRAVAR NO ARQUIVO

 
   ;TENDO O TAMANHO PODEMOS DAR UM "LEA BX,[MENSAGEM+TAMANHO_MENSAGEM]"
   ;E PARTIR DAI DECREMENTAR ATÉ O FINAL
