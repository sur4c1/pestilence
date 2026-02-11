SECTION .text

global fs_enumerate

fs_enumerate:
	mov rax, 217
	syscall
	ret
