BITS 64
start:
endbr64
push rax
mov rax, 57
syscall
test rax, rax
jz thecorruptedhell
pop rax
jmp 0x000000
thecorruptedhell:
