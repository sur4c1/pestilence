SECTION .text

global io_recv

io_recv:
	mov		rax, 0x0				;	Setup for syscall
	syscall							;	Call the syscall

	cmp		rax, 0x0				;	if ret >= 0
	jns		no_errors				;	jump to no error
	xor		rbx, rbx				;	rbx = 0
	sub		rbx, rax				;	rbx -= ret (rbx = -ret)
	mov		rax, 0xFFFFFFFFFFFFFFFF	;	set ret to -1

	no_errors:
	ret								;
