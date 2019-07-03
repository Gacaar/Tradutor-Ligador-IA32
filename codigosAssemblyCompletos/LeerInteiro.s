;Funcao de leitura de inteiro em complemento de 2
;Argumentos: nenhum
;Retorno: Inteiro lido na pilha[EBP+8], quantidade de caracteres lidos em AX
section .data
    mem db ' '
    intLido db ' '

section .text

;Inicio da funcao----------------------------------------------------
LeerInteiro:
enter 0,0

;Le ate 11 caracteres (2^31 tem ateh 10 + 1 de sinal)
mov eax, 3
mov ebx, 0
mov ecx, intLido
mov edx, 11
int 80h

mov eax, 0
cmp byte[intLido], '-'
jne pLeInt
inc eax
pLeInt:
mov edx, 0  ;inteiro
mov ecx, 10  ;num de caracteres
mov ebx, intLido
leitInt:
;Encerra se for enter
cmp byte[ebx+eax], 0Ah
je fimLerInteiro

;edx = 10*edx+byte[ebx+eax]-'0'
push ecx
mov ecx, edx
shl ecx, 3
add ecx, edx
add ecx, edx
mov edx, ecx
movzx ecx, byte[ebx+eax]
sub ecx, '0'
add edx, ecx
pop ecx

inc eax
loop leitInt
fimLerInteiro:

;Se eax+ecx=10 significa que o numero eh positivo (pq comecou da posicao 0)
add eax, ecx
cmp eax, 10 ;O primeiro nao era "-"
je pLeInt2
neg edx
inc edx
pLeInt2:
mov [EBP+8], edx
leave
ret
;Fim da funcao----------------------------------------------------------------------------

global _start
_start: 

;Inicio do trecho que deve ser traduzido, le inteiro e coloca na posicao de memoria 'mem'
push eax
call LeerInteiro
pop eax
mov [mem], eax
;Fim da traducao

mov eax, 1
mov ebx, 0
int 80h