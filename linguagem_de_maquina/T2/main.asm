;Alunos: Ronaldo Tafarel e Luan Chaves

%include "/home/tafaum/Documentos/Faculdade/LM/Implementacoes/computerscien/macro.inc"
extern printf
;----------------------------------------------------------
;MACROS PARA MOVER DADOS DE VARIÁVEL PARA REGISTRADORES
;_movx, assegura que o registrador recebe o tipo correto
;sendo que x é byte,word,ou doubleword (b,w ou d)
;Sintaxe: movx reg, memx, sendo que tamanho de reg 
;deve ser maior ou igual ao tamanho de memx
;----------------------------------------------------------
;move um byte para o registrador
%macro _movb 2
 mov %1,%2        
 ;em cada byte cabem dois digitos hexadecimais
 and %1,0xff ; é o mesmo que and %1,11111111b, pois 1111b=0xF   
%endmacro

;move uma word para o registrador
%macro _movw 2
 mov %1,%2
 and %1,0xffff   
%endmacro

;move um dword para o registrador
%macro _movd 2
 mov %1,%2
 and %1,0xffffffff
%endmacro

section .data   ;seção de definição de variáveis inicializadas

; Mensagem de erro
err:     db      "O arquivo não pode ser aberto!",0xa
len_err:     equ     $ - err   ; tamanho da string err
erroGravacao: db 'Erro na gravação',10
tErroGravacao equ $-erroGravacao

; Alguns modos de abertura de arquivo
 O_RDONLY              equ 0    ;somente leitura
 O_WRONLY              equ 1    ;somente escrita
 O_RDWR                equ 2    ;leitura e escrita
 O_TRUNC               equ 512  ;abre e limpa o arquivo
 O_APPEND              equ 1024 ;inserir no final
 O_CREAT      	       equ 64 

NomeArq: db 'Teste.txt',0
str1  db 'Bem vindo ao mundo da matrix',10,0
TamStr1 equ $-str1
bTamStr1: db 0
fd: db 0
strSucesso db 10,'Arquivo gravado com sucesso',10
tStrSucesso equ $-strSucesso
fmt:    db  "%s"


section .bss      ; seção de variáveis não inicializadas

; Um bufferzinho pra ler o arquivo
buf:     resb   256   ; char buf[256];


section .text
global main   ; diretiva do inicio do codigo
main:    

mov rdi, str1
xor rax,rax ;procura nulo = '\0'
xor rcx,rcx
mov cl, -1
cld
repnz scasb ; o resultado é cx = - tamanho –2
not cl      ; com a operacao not, temos cx = tamanho + 1
dec cl      ; decrementado cx, temos cx = tamanho

mov [bTamStr1],cl  ;variável byte recebe um byte, caso contrário pode sobrepor os proximos endereços
;     ax                 bx          cx         dx
;int open(const char *pathname, int flags);
;int open(const char *pathname, int flags, mode_t mode);
;int creat(const char *pathname, mode_t mode);

;CRIANDO UM ARQUIVO GRAVACAO
    ;mov     rax, 8         ; sycall 8, cria um arquivo 
    ;mov     ebx, NomeArq
    ;int    0x80
    
    
    ;cmp rax,-1            ; se retornar -1 deu erro
    ;je  erro_criacao
    ;mov [qfd],al          
    ;create the file
  
    mov rax,5 ;open
    mov rbx, NomeArq
    mov rcx, O_CREAT | O_RDWR ; mov ecx,O_CREAT + O_RDWR dá na mesma  
    
    mov rdx, 666o ;observar detalhes no modo octal (terminar em o ou começar em 0o)
    ;para ver as permissões do arquivo dê um ls -l arquivo  (no caso, ls -l Teste.txt)
    int 0x80
    cmp rax,-1            ; se retornar -1 deu erro
    je  erro_criacao

    mov [fd],al     ; variável byte recebe byte, caso contrário pode sobrepor os proximos endereços
 
   ;grava no arquivo aberto
    mov rbx,rax
    mov rax,4             ;escrita
    ;_movb rbx,[fd]       ;fd é o descritor do arquivo criado
    mov rcx,str1          ;buffer a ser gravado
    _movb rdx,[bTamStr1]  ;recebe valor em byte 
    int 0x80
    cmp rax,rdx
    jne erro_gravacao
    ;sucesso

    ;invertendo a string str1 em buf
    xor rdi, rdi     ;zera o registrador q vai ser utilizado como índice inicial do buf 
    mov rsi, rdx     ;obtem o tamanho da string para trabalhar como índice final da str1 e ir decrementando 
    ;decrementa duas vezes pois possui o '\0' e o '\n'
    dec rsi
    dec rsi

    ;laco que ocorre a inversão da string
invert: 
    mov al,[str1 + rsi]         ;move o ultimo elemento da string para al
    mov [buf + rdi], al         ;transfere para o buf na posicao edi, que foi zerado acima e incrementado frequentemente
    dec rsi
    inc rdi
    cmp rsi,0
    jge invert
    mov al,[str1 + rdi]
    mov [buf + rdi], al
  
    ;empilha os registradores utilizados na contagem da string para utilizarmos na grvação 
    push rdi
    push rsi

    ;faz a chamada da função printf externa para imprimir a string invertida
    push rbp
    mov rdi, fmt
    mov rsi, buf
    call printf
    pop rbp

    ;desempilha os registradores para utilização na gravação do arquivo
    pop rsi
    pop rdi

    ;gravando a string invertida
    mov rax, 4
    _movb rbx, [fd]				;se usar mov rbx, [fd] da erro
    mov rcx, buf
    mov rdx, rdi				;como no final da inversão de string o tamanho dela está em rdi, apenas movemos para rdx
    int 0x80
    cmp rax,rdx					;verifica se o retorno é igual ao tamanho da string
    jne erro_gravacao

    _printf strSucesso,tStrSucesso
    jmp fim
erro_criacao:
    _printf err, len_err
    jmp fim
erro_gravacao: ;um dos motivos para não criar o arquivo é porque ele já existe
    _printf erroGravacao, tErroGravacao
    
fim:
    ;fecha o arquivo
    mov rax,6
    _movb ebx,[fd]
    int 0x80 
        
    _exit 0






