;Funcao de leitura de string em ASCII
;Argumentos: Endereco para escrever a String lida [EBP+8] e numero de caracteres para ler [EBP+12]
;Retorno: Quantidade de caracteres lidos em EAX
num equ 10
section .data
    mem db '    '

section .text

;Inicio da funcao
LeerString:
enter 0,0

mov eax, 3
mov ebx, 0
mov ecx, [EBP+8]
mov edx, [EBP+12]
int 80h

mov ebx, [EBP+8]
mov ecx, [EBP+12]
mov eax, 0

leitStr:
;Encerra se for enter
cmp byte[ebx+eax], 0Ah
je fimLerString
inc eax
loop leitStr
dec eax ;Nao inclui o enter se nao achar (eh incluido em seguida)
fimLerString:
inc eax ;Inclui o enter se encontra-lo
leave
ret 8
;Fim da funcao

global _start
_start: 

;Inicio do trecho que deve ser traduzido, le string e coloca na posicao de memoria 'mem'
push dword num  ;num eh o numero de caracteres a ser lido
push mem        ;mem eh a label com o endereco onde a string eh salva
call LeerString
;Fim da traducao

;Exibe a string, deve ser apagado
mov edx, eax
mov eax, 4
mov ebx, 1
mov ecx, mem
int 80h
;encerra
mov eax, 1
mov ebx, 0
int 80h