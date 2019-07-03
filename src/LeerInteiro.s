section .data
intLido db ' '

section .text

LeerInteiro:
enter 0,0

mov eax, 3
mov ebx, 0
mov ecx, intLido
mov edx, 11
int 80h

mov eax, 0
cmp byte[intLido], 2Dh
jne POSITIVO
inc eax
POSITIVO:
mov edx, 0
mov ecx, 10
mov ebx, intLido
leitInt:
cmp byte[ebx+eax], 0Ah
je fim

push ecx
shl edx, 3
add edx, edx
add edx, edx
movzx ecx, byte[ebx+eax]
shr ecx, 3*8
sub ecx, 30h
add edx, ecx
pop ecx

inc eax
loop leitInt
fim:

cmp eax, 10
je POSITIVO2
neg edx
inc edx
POSITIVO2:
leave
ret 8