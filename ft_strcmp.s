global ft_strcmp

section .text
ft_strcmp:
	move rdx, 0;
	cmp byte[rdi + rdx], byte [rsi + rdx];
	je .increment;

.increment
	cmp rdx, 
	inc rdx;




a finir
int strcmp(const char *str1, const char *str2);