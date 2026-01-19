;; MMAP

global ft_mmap
extern set_errno

SECTION .text

ft_mmap:
	mov rax, 9
	syscall
	test rax, rax
	js error
	ret

error:
	mov rdi, rax
	neg rdi
	call set_errno
	mov rax, -1
	ret
