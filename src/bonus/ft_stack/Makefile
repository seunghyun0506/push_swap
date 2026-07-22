NAME = ft_stack_bonus.a
INCS = -I./include
OUT_DIR = ./out
SRCS = stack_basic_bonus.c stack_rotate_bonus.c stack_rrotate_bonus.c \
		stack_getter_bonus.c stack_swap_bonus.c stack_push_bonus.c
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
