;; CLOSE

global ft_close

SECTION .text

ft_close:
	mov rax, 3
	syscall
	ret
