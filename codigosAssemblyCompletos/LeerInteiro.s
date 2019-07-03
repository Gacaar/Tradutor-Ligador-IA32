;Funcao de leitura de inteiro
;Argumentos: nenhum
;Retorno: Inteiro lido na pilha[EBP+8], quantidade de caracteres lidos em AX
section .data
    mem db ' '
    intLido db ' '
    T db '1234567890'

section .text

;Inicio da funcao
LeerInteiro:
enter 0,0

;Le ate 11 caracteres (2^31 tem ateh 10 + 1 de sinal)
mov eax, 3
mov ebx, 0
mov ecx, intLido
mov edx, 11
int 80h

mov eax, 0
cmp byte[intLido], 2Dh
jne POSITIVO
inc eax
POSITIVO:
mov edx, 0  ;inteiro
mov ecx, 10
mov ebx, intLido
leitInt:
;Encerra se for enter
cmp byte[ebx+eax], 0Ah
je fim

;edx = 10*edx+byte[ebx+eax]
push ecx
shl edx, 3
add edx, edx
add edx, edx
movzx ecx, byte[ebx+eax]
shr ecx, 3*8 ;Deixa soh o byte desejado, pra nao usar registrador menor que 32 bits
sub ecx, 30h
add edx, ecx
pop ecx

inc eax
loop leitInt
fim:

cmp eax, 10 ;O primeiro nao era "-"
je POSITIVO2
neg edx
inc edx
POSITIVO2:
leave
ret 8
;Fim da funcao

global _start
_start: 

;Inicio do trecho que deve ser traduzido, le string e coloca na posicao de memoria 'mem'
push eax
call LeerInteiro
pop eax
mov [mem], eax
;Fim da traducao

;Exibe a string, deve ser apagado
mov edx, eax
mov eax, 4
mov ebx, 1
mov ecx, T
int 80h
; encerra

mov eax, 1
mov ebx, 0
int 80h