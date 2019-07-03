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
jne pEscrInt
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
add edx, '0'
mov [intWrite+ebx], edx
cmp eax, 0
je fimEscreverInteiro
inc ebx
jmp escrInt
fimEscreverInteiro:

Acrescenta o sinal se for negativo
pop edx
cmp edx, 1
jne pEscrInt2
inc ebx
mov byte[intWrite+ebx], '-'
pEscrInt2:

;Imprime na tela - Imprime de tras pra frente
printInt:
push ebx
mov ecx, ebx
add ecx, intWrite
mov eax, 4
mov ebx, 1
mov edx, 1
int 80h
pop ebx
dec ebx
cmp ebx, 0
jne printInt

;retorna
leave
ret 4

;Fim da funcao ******************************************************************************************************************


global _start
_start: 

;Inicio do trecho que deve ser traduzido, le inteiro e coloca na posicao de memoria 'mem'
push eax
call LeerInteiro
pop eax
;Fim da traducao

;Inicio do trecho que deve ser traduzido, empilha o interio a ser escrito
push eax
call EscreverInteiro
;Fim da traducao

mov eax, 1
mov ebx, 0
int 80h








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