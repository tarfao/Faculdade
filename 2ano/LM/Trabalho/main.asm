%include "/home/tafaum/Documentos/Faculdade/LM/Implementacoes/computerscien/macro.inc"
extern printf

section .data
   MENSAGEM: 		db 'COMPUTER SCIENC IS THE BEST',0   
   tamMENSAGEM: 	db 0
   fmt:    			db "%d",10,0
   msgCalculo: 		db "O tamanho da mensagem é: ",0
   tamMsg: 			db 0
   tamMsgCalc: 		equ $-msgCalculo
   nameArq			db 'msg.txt'

   MsgArq:			db "tarfao"
   tamMsgArq:		equ $ - MsgArq

   aux:				db 0

section .bss		;sessão de variaveis nao inicializadas
	fdin:			resb 1
   fdout:			resb 1
 

section .text
   global main
   main:

   mov rax, 8
   mov rbx, nameArq
   mov edx, 0
   int 0x80

   mov [fdout], rax

   ;CALCULANDO O TAMANHO
   mov rdi, MENSAGEM
   xor al,al ;procura nulo = '\0'
   mov rcx, -1
   cld
   repnz scasb ; cx = - tamanho –2

   not rcx        ;cx = tamanho + 1
   dec rcx
   _printf msgCalculo, tamMsgCalc
 
   mov [tamMsg],rcx

   
   ;CHAMAR FUNCAO printf PARA IMPRIMIR O TAMANHO
   ;
   ;Passa os parâmetros e chama as funções C
   ;mov	rdi,fmt   ;1o parâmetro
   ;mov	rsi,tamMENSAGEM  ;2o parâmetro
   ;mov	rax,0
   ;call printf

   push rbp
   mov rdi, fmt
   mov rsi, [tamMsg]
   call printf

   pop rbp 

  xor rcx,rcx 
  xor rdx,rdx
  xor rbx,rbx
  mov rax,[tamMsg]
_divide:
  mov rbx,10	;EU PODERIA USAR UM OUTRO REGISTRADOR???
  div bl     	;nao se permite div 10, div 3, div 20, etc
  add ah,'0' 	;al quociente, ah é o resto
  push rax   	;deveria empilhar ah, mas temos que empilhar todo o rax, pois ele só empilha todo o registrador
  and ax,0xff	;zera ah: fica somente com al (ax tem 2 bytes e dois nibble de 1 byte), por que dividiu, e só nos interessa a outra parte. ex: 123 div 10, 12->al 3->ah
  inc cl     	;conta elementos na pilha
  cmp al,0
  jnz _divide

_imprimeTopo:
  pop rax
  mov byte [aux],ah ; pega os restos

;=============================================================
;Imprime o caractere 
;=============================================================
  
  mov rax,4      ;escrita
  mov rbx,1      ;fd=1, na tela
  push rcx       ;guarda valor antigo do contador
  mov rcx,aux    ;&buffer a ser impresso
  mov rdx,1      ;tamanho a ser gravado 
  int 0x80
  pop rcx
  dec cl
  cmp cl,0
  jnz _imprimeTopo

   mov rax, 6
   mov rbx, [fdout]
   ;push rax
   ;push rbx
   ;push rdx

   ;pop rdx
   ;pop rbx
   ;pop rax

   ;CRIAR UM ARQUIVO
	;mov    eax, 5         ; sycall 5, abre o arquivo, função open(arquivo,SO_LEITURA) 
    ;mov    ebx, nameArq   ; apontador para onde esta o nome do arquivo
    ;mov    ecx, 0         ; abre o arquivo pra leitura, poderia ser mov ecx, SO_LEITURA
    ;mov    edx, 0         ; indiferente neste caso
    ;int    0x80           ; chama a syscall (no caso, open)

   ;GRAVAR NO ARQUIVO

 
   ;TENDO O TAMANHO PODEMOS DAR UM "LEA BX,[MENSAGEM+TAMANHO_MENSAGEM]"
   ;E PARTIR DAI DECREMENTAR ATÉ O FINAL

   _exit 0