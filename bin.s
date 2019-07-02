section .data
paramChar db '     '

p db '    '

mov eax, 1
mov ebx, 0
int 80h
DOIS EQU 2
OLD_DATA db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
NEW_DATA db 0
TMP_DATA db 0
section .text
mv dword ebx, OLD_DATA
L1: mv dword ebx, DOIS
imul dword ebx
mv dword ebx, eax
mv dword NEW_DATA, ebx
mv dword ebx, DOIS
imul dword ebx
mv dword ebx, eax
mv dword TMP_DATA, ebx
mv dword ebx, OLD_DATA
add dword ebx, DOIS
sub dword ebx, TMP_DATA
mv dword TMP_DATA, ebx
mv dword OLD_DATA, NEW_DATA
mv dword ecx, 1
mv dword OLD_DATA, [NEW_DATA + ecx*4]
mv dword ecx, 1
mv dword [OLD_DATA + ecx*4], NEW_DATA
mv dword ecx, 1
mv dword edx, 1
mv dword [OLD_DATA + edx*4], [NEW_DATA + ecx*4]
mov eax, [TMP_DATA]
push eax
call EscreveChar
push eax
call LeerChar
pop eax
mov [TMP_DATA],eax
mv dword ebx, OLD_DATA
cmp ebx, 0
ja L1
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
