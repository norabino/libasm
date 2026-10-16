NAME        = libasm.a

SRCS        = ft_strlen.s \
              ft_strcpy.s \
              ft_strcmp.s \
              ft_write.s \
              ft_read.s \
              ft_strdup.s \
              ft_calloc.s

OBJS        = $(SRCS:.s=.o)

NASM        = nasm
NFLAGS      = -f elf64

CC          = cc
CFLAGS      = -Wall -Wextra -Werror

%.o: %.s
	$(NASM) $(NFLAGS) $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) test_libasm

fclean: clean
	rm -f $(NAME)

re: fclean all

test: $(NAME)
	$(CC) $(CFLAGS) main.c $(NAME) -o test_libasm
	./test_libasm

.PHONY: all clean fclean re test