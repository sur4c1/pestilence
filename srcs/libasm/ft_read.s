SECTION .text

global ft_read

;ssize_t read(int fd, void *buf, size_t count);
ft_read:
	mov		rax, 0x0				;	Setup for syscall 0 (read)
	syscall							;	Call the syscall

	cmp		rax, 0x0				;	if ret >= 0
	jns		no_errors				;	jump to no error
	xor		rbx, rbx				;	rbx = 0
	sub		rbx, rax				;	rbx -= ret (rbx = -ret)
	mov		rax, 0xFFFFFFFFFFFFFFFF	;	set ret to -1

	no_errors:
	ret								;
