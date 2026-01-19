;; WRITE

global ft_write

SECTION .text

ft_write:
	mov rax, 1
	syscall
	ret
