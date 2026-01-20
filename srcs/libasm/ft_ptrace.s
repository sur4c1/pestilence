;; PTRACE

global ft_ptrace

SECTION .text

ft_ptrace:
	mov rax, 101
	mov rdi, 0
	xor rsi, rsi
	xor rdx, rdx
	xor r10, r10
	syscall
	ret
