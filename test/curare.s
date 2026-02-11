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
mov rax, 1
mov rdi, 1
lea rsi, [rel evil_str]
mov rdx, evil_len
syscall
mov rax, 60
mov rdi, 0
syscall
evil_str: db "hehehehe", 10, 0
evil_len: equ $ - evil_str
