NAME = ft_stack.a
INCS = -I./include
OUT_DIR = ./out
SRCS = stack_basic.c stack_rotate.c stack_rrotate.c \
		stack_getter.c stack_swap.c stack_push.c
OBJS = $(addprefix $(OUT_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OUT_DIR)/%.o : %.c | $(OUT_DIR)
	cc -Wall -Werror -Wextra $(INCS) -c $< -o $@

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

clean:
	rm -rf $(OUT_DIR)

fclean: clean
	rm -f $(NAME)

re:
	fclean all

.PHONY: all clean fclean re
