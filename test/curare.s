BITS 64
push rdi
push rsi
push rdx
mov rax, 1
mov rdi, 1
lea rsi, [rel evil_str]
mov r10, 1
syscall
pop rdx
pop rsi
pop rdi
; mov rax, 60
; mov rdi, 42
; syscall
mov rax, 0x401040
jmp rax
evil_str: db "hehehehe", 10, 0
