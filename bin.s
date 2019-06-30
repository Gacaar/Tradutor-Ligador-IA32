section .text
mv dword [ebx], DOIS
imul dword [ebx]
add dword [ebx], DOIS
sub dword [ebx], TMP_DATA
section .data
