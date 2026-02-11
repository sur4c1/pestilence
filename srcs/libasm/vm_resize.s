global vm_resize

SECTION .text

vm_resize:
	mov rax, 2
	syscall
	ret
