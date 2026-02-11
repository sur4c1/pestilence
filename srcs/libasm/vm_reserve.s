global vm_reserve

SECTION .text

vm_reserve:
	mov rax, 9
	syscall
	test rax, rax
	js error
	ret

error:
	mov rdi, rax
	neg rdi
	mov rax, -1
	ret
