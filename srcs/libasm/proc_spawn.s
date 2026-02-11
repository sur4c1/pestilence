global proc_spawn

SECTION .text

proc_spawn:
	mov rax, 57
	syscall
	ret
