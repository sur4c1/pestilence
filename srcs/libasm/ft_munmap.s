;; MUNMAP

global ft_munmap

SECTION .text

ft_munmap:
	mov rax, 11
	syscall
	ret
