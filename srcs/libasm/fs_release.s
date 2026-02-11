global fs_release

SECTION .text

fs_release:
	mov rax, 3
	syscall
	ret
