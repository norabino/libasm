global ft_calloc

extern malloc
extern __errno_location

section .text
ft_calloc:
	cmp rdi, 0
	je .alloc_zero
	cmp rsi, 0
	je .malloc_zero

	mov rax, rdi
	mul rsi
	jc .overflow

	push rax				; alignement de taille de la pile + sauvegarde taille totale à malloc

	mov rdi, rax
	call malloc

	cmp rax, 0
	je .malloc_error

	pop rcx					; rcx = taille totale
	mov rdx, 0				; rdx = index = 0
	jmp .bzero_loop

.alloc_zero:
	inc rdi
	call malloc
	ret

.overflow:
	push rax				; alignement de taille de la pile
	call __errno_location
	pop rcx

	mov dword [rax], 12
	mov rax ,0
	ret

.malloc_error:
	pop rcx
	ret

.bzero_loop:
	cmp rdx, rcx
	je .done
	mov byte [rax + rdx], 0
	inc rdx
	jmp .bzero_loop

