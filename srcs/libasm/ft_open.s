;; OPEN

global ft_open

SECTION .text

ft_open:
	mov rax, 2
	syscall
	ret
