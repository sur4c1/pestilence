global vm_release

SECTION .text

vm_release:
	mov rax, 11
	syscall
	ret
