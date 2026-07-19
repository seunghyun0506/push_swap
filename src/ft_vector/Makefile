NAME = ft_vector.a
INCS = -I./include
OUT_DIR = ./out
SRC_DIR = ./src
SRCS = vecnew.c vecadd_back.c vecremove.c vecdel.c
OBJS = $(addprefix $(OUT_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c | $(OUT_DIR)
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
