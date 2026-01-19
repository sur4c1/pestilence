;; FSTAT

global ft_fstat

SECTION .text

ft_fstat:
	mov rax, 5
	syscall
	ret
