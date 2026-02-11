global proc_detach

SECTION .text

proc_detach:
	mov rax, 112
	syscall
	ret
