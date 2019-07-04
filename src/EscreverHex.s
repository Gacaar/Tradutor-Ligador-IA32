section .data
hexBytes db '0','0','0','0','0','0','0','0'

section .text

EscreverHex:
enter 0, 0

mov ebx, [EBP+8]
mov edi, 8

loopHex:
mov eax, edi
mov edx, 4
mul edx
sub eax, 4
mov ecx, eax
shr ecx, 28; passo o valor para cl
shr ebx, cl; shift para excluir bits a esq
shl ebx, 28; shift para formato little end

cmp ebx, 10
je aHex
cmp ebx, 11
je bHex
cmp ebx, 12
je cHex
cmp ebx, 13
je dHex
cmp ebx, 14
je eHex
cmp ebx, 15
je fHex
add ebx, 48
jmp set

aHex:
mov ebx, 97
jmp set
bHex:
mov ebx, 98
jmp set
cHex:
mov ebx, 99
jmp set
dHex:
mov ebx, 100
jmp set
eHex:
mov ebx, 101
jmp set
fHex:
mov ebx, 102
jmp set

set:
mov byte [aux+edi], al

dec edi
cmp edi, 0
jne loopHex

mov eax, 4
mov ebx, 1
mov ecx, aux
mov edx, 1
int 80h

leave
ret 4