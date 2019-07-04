;Funcao de escrita de inteiros em complemento de 2
;Argumentos: Inteiro a ser escrito [EBP+8]
;Retorno: Quantidade de caracteres escritos em EAX
section .data
    intWrite db '           '
    intLido db ' '

section .text

;Inico da funcao: ******************************************************************************************************************
EscreverInteiro:
enter 0,0
;Verifica se o numero eh negativo
mov eax, [EBP+8]
mov ebx, eax
shr ebx, 31
cmp ebx, 0
je pEscrInt
mov ebx, 1
push ebx ;flag de negativo
dec eax
neg eax

pEscrInt:

;Transforma em ascii
mov ebx, 0 ;Posicao na string convertida
mov ecx, 10
escrInt:
cdq
idiv ecx ;Resultado em eax e resto em edx
add edx, 30h
mov [intWrite+ebx], edx

; mov eax, 4
; mov ebx, 1
; mov ecx, intWrite
; mov edx, 1
; int 80h

cmp eax, 0
je fimEscreverInteiro
inc ebx
jmp escrInt
fimEscreverInteiro:

; Acrescenta o sinal se for negativo
pop edx
cmp edx, 1
jne pEscrInt2
inc ebx
mov byte[intWrite+ebx], '-'
pEscrInt2:

;Imprime na tela - Imprime de tras pra frente
printInt:
push ebx
mov ecx, intWrite
add ecx, ebx ;ecx = intWrite+ebx
mov eax, 4
mov ebx, 1
mov edx, 1
int 80h
pop ebx
dec ebx
cmp ebx, 0
jge printInt

;retorna
leave
ret 4

;Fim da funcao ******************************************************************************************************************


global _start
_start: 

;Inicio do trecho que deve ser traduzido, empilha o interio a ser escrito
push eax
call EscreverInteiro
;Fim da traducao

mov eax, 1
mov ebx, 0
int 80h