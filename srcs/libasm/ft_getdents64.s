;; GETDENTS64

SECTION .text

global ft_getdents64

ft_getdents64:
	mov rax, 217
	syscall
	ret
