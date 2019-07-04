;Funcao de leitura de inteiro hexadecimal
;Argumentos: nenhum
;Retorno: Inteiro lido na pilha[EBP+8], quantidade de caracteres lidos em AX
section .data
    mem db ' '
    intLido db ' '
    T db '11111111111'

section .text

;Inicio da funcao
LeerHex:
enter 0,0

;Le ate 8 caracteres
mov eax, 3
mov ebx, 0
mov ecx, intLido
mov edx, 8
int 80h

;transforma a string em um numero
sub ebx, ebx
sub ecx, ecx
sub si, si
mov edx, 1

sum:
cmp byte[intLido+ebx], 0Ah; para a execução se achar enter
je fim
cmp byte[intLido+ebx], 41h
je aHex
cmp byte[intLido+ebx], 61h
je aHex
cmp byte[intLido+ebx], 42h
je bHex
cmp byte[intLido+ebx], 62h
je bHex
cmp byte[intLido+ebx], 43h
je cHex
cmp byte[intLido+ebx], 63h
je cHex
cmp byte[intLido+ebx], 44h
je dHex
cmp byte[intLido+ebx], 64h
je dHex
cmp byte[intLido+ebx], 45h
je eHex
cmp byte[intLido+ebx], 65h
je eHex
cmp byte[intLido+ebx], 46h
je fHex
cmp byte[intLido+ebx], 66h
je fHex

movzx eax, byte[intLido+ebx]
sub eax, 30h

finalSum:
mul edx
add ecx, eax
mov eax, edx
mov edi, 16
mul edi
mov edx, eax
inc si
inc ebx
jmp sum

aHex:
mov eax, 10

bHex:
mov eax, 11

cHex:
mov eax, 12

dHex:
mov eax, 13

eHex:
mov eax, 14

fHex:
mov eax, 15

fim:
mov [ebp+8], ecx
mov ax, si

leave
ret 8
;Fim da funcao

global _start
_start: 
;Inicio do trecho que deve ser traduzido, le string e coloca na posicao de memoria 'mem'
push eax
call LeerHex
pop eax
mov [mem], eax
;Fim da traducao

;Exibe uma string, deve ser apagado
mov edx, eax
mov eax, 4
mov ebx, 1
mov ecx, T
int 80h
; encerra

mov eax, 1
mov ebx, 0
int 80h