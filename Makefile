NAME        = push_swap

CFLAGS      = -Wall -Werror -Wextra
DEPFLAGS    = -MMD -MP
INCFLAGS    = -I./include -I./ft_stack/include -I./libft/include

SRC_DIR     = ./src
OUT_DIR     = ./out
INC_DIR     = ./include

SRC_FILES   = main.c push_swap.c push_swap_stat.c check_duplicate.c \
              compute_disorder.c merge_sort.c \
              sort/complex/complex_sort_small.c sort/complex/complex_sort_util.c \
              sort/complex/complex_sort.c sort/three_sort.c \
              sort/medium/medium_sort.c sort/medium/medium_sort_divide.c \
              sort/medium/medium_sort_cost.c sort/medium/medium_sort_return.c \
              sort/simple/simple_sort.c sort/simple/align.c \
              op_buffer/op_buffer.c

SRC         = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ         = $(addprefix $(OUT_DIR)/, $(SRC_FILES:.c=.o))
DEPS        = $(OBJ:.o=.d)

LIBFT       = ./libft
LIBFT_A     = ./libft/libft.a
FT_STACK    = ./ft_stack
FT_STACK_A  = ./ft_stack/ft_stack.a

RM          = rm -rf

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A) $(FT_STACK_A)
	cc $(CFLAGS) $(OBJ) $(FT_STACK_A) $(LIBFT_A) $(INCFLAGS) -o $(NAME)

$(LIBFT_A): FORCE
	make -C $(LIBFT)

$(FT_STACK_A): FORCE
	make -C $(FT_STACK)


$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	cc $(CFLAGS) $(DEPFLAGS) $(INCFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(DEPS)
	make -C $(LIBFT) clean
	make -C $(FT_STACK) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT) fclean
	make -C $(FT_STACK) fclean

re: fclean all

-include $(DEPS)

.PHONY: FORCE all clean re fclean
