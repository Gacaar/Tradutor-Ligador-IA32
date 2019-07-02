;Funcao de leitura de char em ASCII
;Argumentos: nenhum
;Retorno: Caracter lido na pilha, quantidade de caracteres lidos em AX
section .data
    mem db '    '
    p db '    '

section .text
;Inicio da funcao
LeerChar:
enter 0,0

mov eax, 3
mov ebx, 0
mov ecx, p
mov edx, 1
int 80h

mov eax, [p]
mov [EBP+8], eax
mov eax, 1

leave
ret
;Fim da funcao

global _start
_start: 

;Inicio do trecho que deve ser traduzido, le caracter e coloca na posicao de memoria 'mem'
push eax
call LeerChar
pop eax
mov [mem],eax
;Fim da traducao

;Exibe o caracter, deve ser apagado
mov eax, 4
mov ebx, 1
mov ecx, mem
mov edx, 1
int 80h
;encerra
mov eax, 1
mov ebx, 0
int 80h