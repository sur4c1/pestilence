BITS 64
start:
endbr64
push rax
mov rax, 57
syscall
test rax, rax
jz 0x000000
pop rax
jmp 0x000000
