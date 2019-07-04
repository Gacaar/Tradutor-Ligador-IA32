;Funcao de escrita de inteiros em hexadecimal
;Argumentos: Inteiro a ser escrito [EBP+8]
;Retorno: Quantidade de caracteres escritos em EAX
section .data
    mem dd 0x31323334
    aux db '0','0','0','0','0','0','0','0'
    flag db 'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa'
    flag2 db 'b'
section .text

;Inicio da funcao
EscreverHex:
enter 0, 0

mov ebx, [EBP+8]
mov edi, 8

loopHex:
mov eax, edi
mov edx, 4
mul edx
sub eax, 4
mov ecx, eax
shr ecx, 28; passo o valor para cl
shr ebx, cl; shift para excluir bits a esq
shl ebx, 28; shift para formato little end

cmp ebx, 10
je aHex
cmp ebx, 11
je bHex
cmp ebx, 12
je cHex
cmp ebx, 13
je dHex
cmp ebx, 14
je eHex
cmp ebx, 15
je fHex
add ebx, 48
jmp set

aHex:
jmp set
bHex:
jmp set
cHex:
jmp set
dHex:
jmp set
eHex:
jmp set
fHex:
jmp set

set:
mov byte [aux+edi], al

dec edi
cmp edi, 0
jne loopHex

mov eax, 4
mov ebx, 1
mov ecx, aux
mov edx, 1
int 80h

leave
ret 4
;Fim da funcao

global _start
_start: 

;Inicio do trecho que deve ser traduzido, le string e coloca na posicao de memoria 'mem'
push DWORD mem

call EscreverHex
;Fim da traducao

mov eax, 1
mov ebx, 0
int 80h