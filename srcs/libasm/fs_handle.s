global fs_handle

SECTION .text

fs_handle:
	mov rax, 2
	syscall
	ret
