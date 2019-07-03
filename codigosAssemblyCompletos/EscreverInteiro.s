;Funcao de escrita de inteiros em complemento de 2
;Argumentos: Inteiro a ser escrito [EBP+8]
;Retorno: Quantidade de caracteres escritos em EAX
section .data
    intWrite db '          '

section .text

;Inico da funcao:

;Verifica se o numero eh negativo
mov eax, [EBP+8]
cmp byte[EBP+8], 0
jne POSITIVO
dec eax
neg eax
 
POSITIVO:

;Transforma em ascii
mov ebx, 0 ;Posicao na string convertida
mov edx, 0 ;Recebe o resto da divisao



;edx

;Acrescenta o sinal se for negativo

;Imprime na tela


;Fim da funcao


global _start
_start: 

;Inicio do trecho que deve ser traduzido, le inteiro e coloca na posicao de memoria 'mem'
push eax
call EscreverInteiro
;Fim da traducao