global vm_flush

SECTION .text

vm_flush:
	mov rax, 28
	syscall
	ret
