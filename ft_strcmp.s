global ft_strcmp

section .text
ft_strcmp:
	mov rcx, 0

.loop:
	mov al, byte[rdi + rcx]
	mov dl, byte[rsi + rcx]

	cmp al, dl
	jne .diff

	cmp al, 0
	je .same

	inc rcx
	jmp .loop


.diff:
	movzx rax, al
	movzx rdx, dl
	sub rax, rdx
	ret

.same:
	mov rax, 0
	ret
