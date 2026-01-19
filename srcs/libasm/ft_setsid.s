;; SETSID

global ft_setsid

SECTION .text

ft_setsid:
	mov rax, 112
	syscall
	ret
