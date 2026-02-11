global fs_query

SECTION .text

fs_query:
	mov rax, 6
	syscall
	ret
