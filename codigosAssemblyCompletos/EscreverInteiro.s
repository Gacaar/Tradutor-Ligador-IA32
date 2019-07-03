;Funcao de escrita de inteiros em complemento de 2
;Argumentos: Inteiro a ser escrito [EBP+8]
;Retorno: Quantidade de caracteres escritos em EAX
section .data
    intWrite db '           '

section .text

;Inico da funcao:
EscreverInteiro:

;Verifica se o numero eh negativo
mov eax, [EBP+8]
cmp byte[EBP+8], 0
jne pEscrInt
mov ebx, 1
push ebx ;flag de negativo
dec eax
neg eax
 
pEscrInt:

;Transforma em ascii
mov ebx, 11 ;Posicao na string convertida - escreve de tras pra frente pra nao fazer shift
mov edx, 0 ;Recebe o resto da divisao
mov ecx, 10
escrInt:
cdq
div ecx ;Resultado em eax e resto em edx
add edx, '0'
mov [intWrite+ebx], edx
cmp eax, 0
je fimEscreverInteiro
dec ebx
jmp escrInt
fimEscreverInteiro:

;Acrescenta o sinal se for negativo
pop edx
cmp edx, 1
jne pEscrInt2
dec ebx
mov byte[intWrite+ebx], '-'
pEscrInt2:

;Imprime na tela
sub ebx, 11
mov edx, ebx
mov eax, 4
mov ebx, 1
mov ecx, intWrite

;retorna
leave
ret 4

;Fim da funcao


global _start
_start: 

;Inicio do trecho que deve ser traduzido, empilha o interio a ser escrito
push eax
call EscreverInteiro
;Fim da traducao