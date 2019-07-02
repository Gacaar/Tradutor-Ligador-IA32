;Funcao de escrita de char em ASCII
;Argumentos: char na pilha
;Retorno: Quantidade de caracteres escritos em AX
section .data
    mem db 'f   '
    p db '     '

section .text
;Inicio da funcao ----------------
EscreveChar:
enter 0,0

mov eax, [EBP+8]
mov [p], eax

mov eax, 4
mov ebx, 1
mov ecx, p
mov edx, 1
int 80h

mov eax, 1

leave 
ret 4 ;Desempilha o parametro de tamanho 4 bytes (eax)
;Fim da funcao -----------------------

global _start
_start: 

;Inicio do trecho que deve ser traduzido, empilha o caracter a ser escrito na pilha
mov eax, [mem]
push eax
call EscreveChar
; ;Fim da traducao

;encerra
mov eax, 1
mov ebx, 0
int 80h