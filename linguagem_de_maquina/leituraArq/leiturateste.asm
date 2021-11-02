section .data   ;seção de definição de variáveis inicializadas

; Mensagem de erro
err     db      "O arquivo não pode ser aberto!",0xa
len_err     equ     $ - err   ; tamanho da string err

; Alguns modos de abertura de arquivo
SO_LEITURA equ 	00      ;somente leitura
SO_ESCRITA equ	01
CRIA_ARQ   equ  0100

; File descriptors (fd)
TECLADO    equ     0  ; codigo do fd da entrada padrao  #define TECLADO 0, ou const TECLADO = 0
TELA       equ     1  ; codigo do fd da saida padrao

; Nome do arquivo
arquivo db "teste.txt", 0x0  ; char *arquivo="texte.txt"

section .bss      ; seção de variáveis não inicializadas

; Um bufferzinho pra ler o arquivo
buf     resb   256   ; char buf[256];

section .text   ; seção onde escrevo o codigo  
global _start   ; diretiva do inicio do codigo
_start:         ;    

; Abre o arquivo para leitura

    mov    rax, 5         ; sycall 5, abre o arquivo, função open(arquivo,SO_LEITURA) 
    mov    ebx, arquivo   ; apontador para onde esta o nome do arquivo
    mov    ecx, 0         ; abre o arquivo pra leitura, poderia ser mov ecx, SO_LEITURA
    mov    edx, 0         ; indiferente neste caso
    int    0x80           ; chama a syscall (no caso, open)

    cmp    rax, 1         ; se o arquivo nao foi aberto, exibe erro
    jge    leitura        ; jump if great or equal, salta para leitura se sucesso

;não foi bem sucedido, então imprime mensagem de erro
    mov    rax, 4         ; serviço de escrita
    mov    ebx, 1      ; ou mov ebx, STDOUT    ; escreve msg de erro na tela
    mov    ecx, err      ; define o buffer err para impressao[0]
    mov    edx, len_err   ;define quantos caracteres a imprimir a partir de buffer[0]
    int    0x80           ; chama a syscall write(ebx,err,len_err)
    jmp fim

leitura:
    ; Le do arquivo 
    push   rax             ; salva o conteudo de eax na pilha
    mov    rbx, rax        ; guarda o descritor (fd) que estava em eax
    mov    ecx, buf        ; ptr do inicio de buf
    mov    edx, 256          ; numero de bytes que eu quero
    mov    rax, 3          ; se eu tivesse feito primeiro mov eax, 3 eu perderia o valor do fd
    int    0x80            ; chama a syscall read(ebx,ecx,edx) ou read(fd,buf,256)
    ;retorna -1 em eax se deu erro de leitura ou o numero de caracteres lido se sucesso
    
; Imprime o conteudo na tela 
    mov    edx, eax         ; tamanho da mensagem
    mov    ecx, buf         ; endereco inicial da mensagem
    mov    ebx, 1           ; ou mov    ebx, TELA,       ; 
    mov    rax, 4           ; serviço de impressao
    int    0x80             ; chama a syscall write(1,buf,edx)

fim:
    mov rax,0
    mov ebx,0
    int 0x80   ;syscall exit(0)

