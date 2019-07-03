section .data

section .text

EscreverString:
enter 0,0

mov ebx, [EBP+8]
mov ecx, [EBP+12]
mov eax, 0

escrStr:
cmp byte[ebx+eax], 0Ah
je fim
inc eax
loop escrStr
dec eax
fim:
inc eax

mov edx, eax
mov eax, 4
mov ebx, 1
mov ecx, [EBP+8]
int 80h

leave
ret 8