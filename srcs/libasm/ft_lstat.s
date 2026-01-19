;; LSTAT

global ft_lstat

SECTION .text

ft_lstat:
	mov rax, 6
	syscall
	ret
