;Funcao de escrita de string em ASCII
;Argumentos: Endereco para ler a String [EBP+8] e numero de caracteres para escrever [EBP+12]
;Retorno: Quantidade de caracteres escritos em EAX
num equ 13
section .data
    mem db '123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ',0Ah
    intLido db ' '

section .text

;Inicio da funcao
EscreverString:
enter 0,0

mov ebx, [EBP+8]
mov ecx, [EBP+12]
mov eax, 0

escrStr:
cmp byte[ebx+eax], 0Ah
je fim2
inc eax
loop escrStr
dec eax ;Decrementa se nao encontrar enter (que eh contado em seguida)
fim2:
inc eax ;Inclui o enter caso ache ele

mov edx, eax
mov eax, 4
mov ebx, 1
mov ecx, [EBP+8]
int 80h

leave
ret 8
;Fim da funcao

global _start
_start: 

;Inicio do trecho que deve ser traduzido, le inteiro e coloca na posicao de memoria 'mem'
push eax
call LeerInteiro
pop eax
;Fim da traducao

;Inicio do trecho que deve ser traduzido
push eax  ;num eh o numero de caracteres a serem escritos
push mem        ;mem eh a label com o endereco onde a string esta salva
call EscreverString
;Fim da traducao

;encerra
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
jne POSITIVO
inc eax
POSITIVO:
mov edx, 0  ;inteiro
mov ecx, 10  ;num de caracteres
mov ebx, intLido
leitInt:
;Encerra se for enter
cmp byte[ebx+eax], 0Ah
je fim

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
fim:

;Se eax+ecx=10 significa que o numero eh positivo (pq comecou da posicao 0)
add eax, ecx
cmp eax, 10 ;O primeiro nao era "-"
je POSITIVO2
neg edx
inc edx
POSITIVO2:
mov [EBP+8], edx
leave
ret
;Fim da funcao----------------------------------------------------------------------------