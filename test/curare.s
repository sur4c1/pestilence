BITS 64
start:
push rdi
push rsi
push rdx
push rbx
mov rax, 1
mov rdi, 1
lea rsi, [rel evil_str]
mov rdx, evil_len
syscall
lea rax, [rel start] ;; EFFECTIVE OFF
mov rbx, 0xAAAAAAAAAAAAAAAA;; SUPPOSED OFF
sub rax, rbx
mov rbx, 0xBBBBBBBBBBBBBBBB;; E_ENTRY
add rax, rbx
pop rbx
pop rdx
pop rsi
pop rdi
; mov rax, 60
; mov rdi, 42
; syscall
jmp rax
evil_str: db "hehehehe", 10, 0
evil_len: equ $ - evil_str
