section .data
    HexLido db ' '

section .text

LeerHex:
enter 0,0

mov eax, 3
mov ebx, 0
mov ecx, hexLido
mov edx, 8
int 80h

sub ebx, ebx
sub ecx, ecx
sub si, si
mov edx, 1

sum:
cmp byte[hexLido+ebx], 0Ah
je fim
cmp byte[hexLido+ebx], 41h
je aHex
cmp byte[hexLido+ebx], 61h
je aHex
cmp byte[hexLido+ebx], 42h
je bHex
cmp byte[hexLido+ebx], 62h
je bHex
cmp byte[hexLido+ebx], 43h
je cHex
cmp byte[hexLido+ebx], 63h
je cHex
cmp byte[hexLido+ebx], 44h
je dHex
cmp byte[hexLido+ebx], 64h
je dHex
cmp byte[hexLido+ebx], 45h
je eHex
cmp byte[hexLido+ebx], 65h
je eHex
cmp byte[hexLido+ebx], 46h
je fHex
cmp byte[hexLido+ebx], 66h
je fHex

movzx eax, byte[hexLido+ebx]
sub eax, 30h

finalSum:
mul edx
add ecx, eax
mov eax, edx
mov edi, 16
mul edi
mov edx, eax
inc si
jmp sum

aHex:
mov eax, 10

bHex:
mov eax, 11

cHex:
mov eax, 12

dHex:
mov eax, 13

eHex:
mov eax, 14

fHex:
mov eax, 15

fim:
mov [ebp+8], ecx
mov ax, si

leave
ret 8