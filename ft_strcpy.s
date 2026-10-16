global ft_strcpy

section .text
ft_strcpy:
	mov rax, rdi
	mov rcx, 0

.loop:
	mov dl, byte [rsi + rcx]
	mov byte [rdi + rcx], dl

	cmp dl, 0
	je .done

	inc rcx
	jmp .loop

.done:
	ret

section .note.GNU-stack noalloc noexec nowrite progbits