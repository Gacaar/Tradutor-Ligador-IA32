section .data
p db '    '

section .text
LeerChar:
enter 0,0

mov eax, 3
mov ebx, 0
mov ecx, p
mov edx, 1
int 80h

mov eax, [p]
mov [EBP+8], eax
mov eax, 1

leave
ret