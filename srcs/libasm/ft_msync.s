;; MSYNC

global ft_msync

SECTION .text

ft_msync:
	mov rax, 28
	syscall
	ret
