;compilar:   nasm -g -f elfx hello.asm  onde x=32 ou x=64, geraria um hello.o (o -g é para debuggar e o -f é para definir a saída, do binário para linux)
;linkeditar: ld hello.o  -o hello      o objeto será o hello determinado pelo -o 
;executar:   ./hello

; ISTO É UM COMENTARIO

section .data                        ;definindo a seção ou segmento de dados (variáveis)

  TECLADO equ 0                      ;DESCRITOR DE TECLADO
  TELA equ 1                         ;DESCRITOR DE TELA
  msgNome db 'Entre com seu nome: '  ;definindo uma string 
  tamMsgNome   equ $ - msgNome       ;constante com o tamanho da string(o $ faz uma conta da última posicao menos a primeira e obtem em tam o tamanho da string)
  strNome times 20 db 0              ;char strnome[20]={0,0,0,...,0}
  msgBoasVindas db 'Bem Vindo,'
  tamMsgBoasVindas equ $ - msgBoasVindas
  numCharLidos db 0
;enddata

%macro _printf 2    ;o numero 2 representa a quantidade de parametros
    mov rax,4
    mov rbx,TELA
    mov rcx,%1      ;representa o parametro 1 que é o buffer a ser gravado
    mov rdx,%2      ;representa o tamanho do buffer a ser gravado
    int 0x80
%endmacro

%macro _scanf 2
    mov rax,3
    mov rbx,TECLADO
    mov rcx,%1
    mov rdx,%2
    int 0x80
%endmacro


section .text                  ;segmento ou seção de codigo(pode ser segment .text)
  global _start                ;diretiva que define o inicio de codificacao (label _start)pode escrever qualquer coisa, global _main

  _start:                      ;label (a partir daqui começa a executar o programa), poderia ser _main, como dito acima
  
  								;As linhas 18, 19 e 20 equivale a fwrite(1,hello,tam)
  ;mov rax,4                    ;seta serviço 4, de impressão  
  ;mov rbx,1                           ;seta o local de impressão, a tela do computador
  ;mov rcx,msgNome                     ;indica o que irá imprimir, o conteúdo de hello
  ;mov rdx,tamMsgNome                  ;indica o numero de caracteres a imprimir a partir do inicio de hello
  ;int 0x80                     ;realiza a interrupção (syscall), conforme o serviço solicitado(depois desse retorno que verifica o que foi setado em eax)

  _printf msgNome,tamMsgNome

  ;  ssize_t read(int fd, void *buf, size_t count);
  ;  numChraLidos = read(  0(descritor de teclado), strNome, 20);
  ; if (numCharLidos == -1) printf("erro de leitura)
  ;  numCharLidos é a quantidade de caracteres digitados
 
  ;mov rax,3                 ; servico de leitura, read (eax é para 32bits e rax é para 64 bits);
  ;mov rbx,0                 ; descritor de teclado, vamos pegar a palavra do teclado
  ;mov rcx,strNome           ; é a string que vai receber o nome digitado 
  ;mov rdx,20                ;é o maximo de letras digitadas
  ;int 0x80                  ; realiza a interrupção e volta para executar, retorna o numero de caracteres digitados em rax
  _scanf strNome,20
  mov [numCharLidos], rax    ;obtem o que tem no acumulador ax para tamNome, o que tem no acumulador é a palavra digitada


  ;mov rax,4                    ;seta serviço 4, de impressão  
  ;mov rbx,1                           ;seta o local de impressão, a tela do computador
  ;mov rcx,msgBoasVindas                    ;indica o que irá imprimir, o conteúdo de hello
  ;mov edx,tamMsgBoasVindas                 ;indica o numero de caracteres a imprimir a partir do inicio de hello
  ;int 0x80                     ;realiza a interrupção (syscall), conforme o serviço solicitado(depois desse retorno que verifica o que foi setado em eax)

  _printf msgBoasVindas,tamMsgBoasVindas

  ;mov rax,4
  ;mov rbx,1
  ;mov rcx,strNome
  ;mov rdx, [numCharLidos]
  ;int 0x80
  _printf strNome,[numCharLidos]

  mov eax,1                    ;seta serviço 1, função exit(essas ultimas linhas são precisas em qualquer programa)
  mov ebx,0                    ;passa o parâmetro 0 (exit(0) em C)
  int 0x80                     ;realiza a interrupção
;endtext




