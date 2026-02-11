global io_query

SECTION .text

io_query:
	mov rax, 5
	syscall
	ret
