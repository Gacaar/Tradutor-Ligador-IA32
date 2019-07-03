section .data

section .text

LeerString:
enter 0,0

mov eax, 3
mov ebx, 0
mov ecx, [EBP+8]
mov edx, [EBP+12]
int 80h

mov ebx, [EBP+8]
mov ecx, [EBP+12]
mov eax, 0

leitStr:

cmp byte[ebx+eax], 0Ah
je fim
inc eax
loop leitStr
dec eax
fim:
inc eax
leave
ret 8