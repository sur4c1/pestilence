;; MREMAP

global ft_mremap

SECTION .text

ft_mremap:
	mov rax, 2
	syscall
	ret
