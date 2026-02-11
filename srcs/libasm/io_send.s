global io_send

SECTION .text

io_send:
	mov rax, 1
	syscall
	ret
