;Funcao de escrita de string em ASCII
;Argumentos: Endereco para ler a String [EBP+8] e numero de caracteres para escrever [EBP+12]
;Retorno: Quantidade de caracteres escritos em EAX
num equ 13
section .data
    mem db 'Hello World!',0Ah

section .text

;Inicio da funcao
EscreverString:
enter 0,0

mov ebx, [EBP+8]
mov ecx, [EBP+12]
mov eax, 0

escrStr:
cmp byte[ebx+eax], 0Ah
je fimEscreverString
inc eax
loop escrStr
dec eax ;Decrementa se nao encontrar enter (que eh contado em seguida)
fimEscreverString:
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

;Inicio do trecho que deve ser traduzido
push dword num  ;num eh o numero de caracteres a serem escritos
push mem        ;mem eh a label com o endereco onde a string esta salva
call EscreverString
;Fim da traducao

;encerra
mov eax, 1
mov ebx, 0
int 80h