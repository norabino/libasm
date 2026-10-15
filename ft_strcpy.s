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
	je .loop

.done:
	ret