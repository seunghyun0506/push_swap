NAME = ft_stack.a
INCS = -I./include
HEADER = ft_stack.h
SRCS = stack_basic.c stack_rotate.c stack_rrotate.c \
		stack_getter.c stack_swap.c
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o : %.c
	cc -Wall -Werror -Wextra $(INCS) -c $< -o $@

fclean:
	rm -rf obj
	rm -f $(NAME)

.PHONY:
	NAME
