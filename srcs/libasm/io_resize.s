global io_resize

SECTION .text

io_resize:
	mov rax, 77
	syscall
	ret
