;; FORK

global ft_fork

SECTION .text

ft_fork:
	mov rax, 57
	syscall
	ret
