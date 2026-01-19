;; EXIT

global ft_exit

SECTION .text

ft_exit:
	mov rax, 60
	syscall
	ret
