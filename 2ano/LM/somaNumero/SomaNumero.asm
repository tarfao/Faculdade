;COMPILAR: nasm -g -f elfX SomaNumero.asm  ===> gera um SomaNumero.o      (X=64 ou X=32)
;LINKAR  : ld SomaNumero.o -o SomaNumero   ===> gera um SomaNumero
;AOS NAVEGANTES: QUEM TEM MÁQUINA COM 32 favor mudar todos os 'r' dos registradores para 'e'
;Desse modo, onde temos rax,rbx,rcx, ... fica eax, ebx,ecx,...
;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
%include "macro.inc"

section .data
  MsgNum1:          db 'Entre com o primeiro número: '
  tMsgNum1:        equ $- MsgNum1 ; $ é a posição após a alocação de bytes por MsgNum1
  MsgNum2:          db 'Entre com o segundo número: '
  tMsgNum2:        equ $- MsgNum2 ; 
  MsgResultado:     db 'Resultado da soma: '
  tMsgResultado:   equ $- MsgResultado ; 
  strNum1: times 10 db 0; mesmo que char strNum1[]={0,0,0,...,0}, um vetor com 10 celulas e zerado
  tamNum1:          db 0     ;obtem o tamanho da string a ser lida
  strNum2: times 10 db 0
  tamNum2:          db 0
                   ;Uma solucao mais engenhosa, seria guardar o tamanho lido dentro do proprio strNum. Assim:
                   ;strNum db 10,times 10 db 0, FUNCIONAVA em Masm
  Num1:             db 0
  Num2:             db 0
  aux:              db 0
  pulaLinha:        db 10
;enddata  

;-------------------------------------------------------------
;mov ou lea ?
;-------------------------------------------------------------
;lea pega sempre o endereço
;mov ebx,vetor    ==  lea ebx, [vetor]   ==  ebx=&vetor, em C 
;lea ebx,[vetor+10]  ==  ebx = &(vetor+10)
;mov ebx,[vetor+10] não é permitido
;o nasm não consegue calcular o endereço e pegar o valor
;na variável
;Se quizessemos usar vetor[10] (ou *(vetor+10)), temos 
;que usar [ebx]
;-------------------------------------------------------------

section .text
  global _start

_start:
;=============================================================
;Leitura do primeiro numero
;=============================================================

  _printf MsgNum1, tMsgNum1
  _scanf strNum1,10 
  mov [tamNum1],al
  dec byte [tamNum1]

;=============================================================
;Leitura do segundo numero
;=============================================================  

  _printf MsgNum2, tMsgNum2
  _scanf strNum2,10 
  mov [tamNum2],al
  dec byte [tamNum2]

;===========================================================================  
;_Str2Num num1,strNum1,tamNum1;
;===========================================================================
  xor eax, eax     ;zera eax
  xor rcx,rcx       ;cx será o contador
  mov ebx,strNum1  ;
  ;eu quero um byte, se fizer mov cx, pego dois bytes a partir de &strNum
  ;se fizer mov ecx, pego 4 bytes, mov rax, pego 8 bytes
  mov cl,[tamNum1]     ;ecx = *tamanhoStr
  ;Uma maneira de pegar somente o byte de um endereço seria
  ;and ecx,0x00ff
  xor esi,esi;zera o índice
gera_num1:
  mov dl,10       ;dl é 1 byte, dx = dh:dl, 16 bits, edx tem 32 bits, rdx 64 bits
  mul dl          ;não é permitido operação mul 10 
                  ;tem que ser variavel ou registrador, o resultado ficará em ax
  sub byte [ebx+esi],'0'
  add al, [ebx+esi]
  inc esi
  dec cl
  cmp cl,0
  jnz gera_num1
  mov [Num1],ax ;passa o valor
    
;===========================================================================
;_Str2Num num2,strNum2,tamNum2;
;===========================================================================
  xor eax, eax     ;zera eax
  xor rcx,rcx
  mov ebx,strNum2  ;
  ;eu quero um byte, se fizer mov cx, pego dois bytes a partir de &strNum
  ;se fizer mov ecx, pego 4 bytes, mov rax, pego 8 bytes
  mov cl,[tamNum2]     ;ecx = *tamanhoStr
  ;Uma maneira de pegar somente o byte de um endereço seria
  ;and ecx,0x00ff
  xor esi,esi;zera o índice
gera_num2:
  mov dl,10                 ;dl é 1 byte, dx = dh:dl, 16 bits, edx tem 32 bits, rdx 64 bits
  mul dl                    ;não é permitido operação mul 10 
                            ;tem que ser variavel ou registrador, o resultado ficará em ax
  sub byte [ebx+esi],'0'    ;subtrai o número referente ao seu caracter(numero) na tabela ascii, pelo 0, que esta na posicao 48 decimal, e vai até 9
  add al, [ebx+esi]         ;faz o somatório do acumulador com a subtração feita acima
  inc esi
  dec cl
  cmp cl,0
  jnz gera_num2
  mov [Num2],ax ;passa o valor, pode ser al
  
;===========================================================================
;Soma os numeros
;===========================================================================
  mov al, [Num1]
  add al, [Num2] ;resultado da soma em *Num2
  
;===========================================================================   
;_printNum  ;macro para imprimir eax em formato decimal
;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
;===========================================================================
; Código em C
;===========================================================================
; contadorPilhaCX=0;
; _divide:
; restoAH= acumuladorAX - int(acumuladorAX/10)*10;
; push(RestoAH);   -> joga na pilha
; acumuladorAX = int(acumuladorAX/10);
; contadorPilhaCX++;
; if(acumuladorAX) goto _divide;
;
;===========================================================================
  xor rcx,rcx 
  xor rdx,rdx
  xor rbx,rbx
_divide:
  mov rbx,10	;EU PODERIA USAR UM OUTRO REGISTRADOR???
  div bl     ;nao se permite div 10, div 3, div 20, etc
  add ah,'0' ;al quociente, ah é o resto
  push rax   ;deveria empilhar ah, mas temos que empilhar todo o rax, pois ele só empilha todo o registrador
  and ax,0xff;zera ah: fica somente com al (ax tem 2 bytes e dois nibble de 1 byte), por que dividiu, e só nos interessa a outra parte. ex: 123 div 10, 12->al 3->ah
  inc cl     ;conta elementos na pilha
  cmp al,0
  jnz _divide
 
;=============================================================
;Imprime mensagem Resultado:
;=============================================================
  push rcx
  _printf MsgResultado, tMsgResultado
  pop rcx 
;===========================================================================
; Código em C
;===========================================================================
; Pop(RestoDX);
;_imprimeTopo:
; printf("%d",RestoDX);
; contadorPilhaCX--;
; if(acumuladorAX) goto _ImprimeTopo;
;
;===========================================================================
 
_imprimeTopo:
  pop rax
  mov byte [aux],ah ; pega os restos

;=============================================================
;Imprime o caractere 
;=============================================================
  
  mov eax,4      ;escrita
  mov ebx,1      ;fd=1, na tela
  push rcx       ;guarda valor antigo do contador
  mov ecx,aux    ;&buffer a ser impresso
  mov edx,1      ;tamanho a ser gravado 
  int 0x80
  pop rcx
  dec cl
  cmp cl,0
  jnz _imprimeTopo
 
;=============================================================
;Pula Linha
;=============================================================
  _printf pulaLinha,1
;  mov eax,4          ;escrita
;  mov ebx,1          ;fd=1, na tela
;  mov ecx,pulaLinha  ;&buffer a ser impresso
;  mov edx,1          ;tamanho a ser gravado 
;  int 0x80

 
;=============================================================
;exit 0
;============================================================= 
  mov eax,1     
  mov ebx,0    
  int 0x80

;endtext  


  
  
   
    
