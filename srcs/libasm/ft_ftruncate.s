;; FTRUNCATE

global ft_ftruncate

SECTION .text

ft_ftruncate:
	mov rax, 77
	syscall
	ret
