global proc_terminate

SECTION .text

proc_terminate:
	mov rax, 60
	syscall
	ret
