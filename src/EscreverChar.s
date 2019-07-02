section .data
paramChar db '     '

section .text
EscreveChar:
enter 0,0

mov eax, [EBP+8]
mov [paramChar], eax

mov eax, 4
mov ebx, 1
mov ecx, paramChar
mov edx, 1
int 80h

mov eax, 1

leave 
ret 4