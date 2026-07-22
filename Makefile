NAME        = push_swap
NAME_BONUS  = checker

CFLAGS      = -Wall -Werror -Wextra
DEPFLAGS    = -MMD -MP
INCFLAGS    = -I./include -I./ft_stack/include -I./src/bonus/ft_stack/include -I./libft/include

SRC_DIR     = ./src
OUT_DIR     = ./out
INC_DIR     = ./include

SRC_FILES   = main.c push_swap.c push_swap_stat.c check_duplicate.c \
              compute_disorder.c merge_sort.c print_bench.c \
              sort/complex/complex_sort_small.c sort/complex/complex_sort_util.c \
              sort/complex/complex_sort.c sort/three_sort.c \
              sort/medium/medium_sort.c sort/medium/medium_sort_divide.c \
              sort/medium/medium_sort_return.c \
              sort/simple/simple_sort.c sort/simple/align.c \
              sort/simple/simple_sort_cost.c \
              op_buffer/op_buffer.c

SRC_BONUS   = bonus/checker_bonus.c bonus/checker_util_bonus.c \
              push_swap.c push_swap_stat.c check_duplicate.c \
              compute_disorder.c merge_sort.c print_bench.c \
              sort/complex/complex_sort_small.c sort/complex/complex_sort_util.c \
              sort/complex/complex_sort.c sort/three_sort.c \
              sort/medium/medium_sort.c sort/medium/medium_sort_divide.c \
              sort/medium/medium_sort_return.c \
              sort/simple/simple_sort.c sort/simple/align.c \
              sort/simple/simple_sort_cost.c \
              op_buffer/op_buffer.c

SRC         = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ         = $(addprefix $(OUT_DIR)/, $(SRC_FILES:.c=.o))
DEPS        = $(OBJ:.o=.d)

OBJ_BONUS   = $(addprefix $(OUT_DIR)/, $(SRC_BONUS:.c=.o))
DEPS_BONUS  = $(OBJ_BONUS:.o=.d)

LIBFT             = ./libft
LIBFT_A           = ./libft/libft.a
FT_STACK          = ./ft_stack
FT_STACK_A        = ./ft_stack/ft_stack.a
FT_STACK_BONUS    = ./src/bonus/ft_stack
FT_STACK_BONUS_A  = ./src/bonus/ft_stack/ft_stack_bonus.a

RM          = rm -rf

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A) $(FT_STACK_A)
	cc $(CFLAGS) $(OBJ) $(FT_STACK_A) $(LIBFT_A) $(INCFLAGS) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS) $(LIBFT_A) $(FT_STACK_BONUS_A)
	cc $(CFLAGS) $(OBJ_BONUS) $(FT_STACK_BONUS_A) $(LIBFT_A) $(INCFLAGS) -o $(NAME_BONUS)

$(LIBFT_A): FORCE
	make -C $(LIBFT)

$(FT_STACK_A): FORCE
	make -C $(FT_STACK)

$(FT_STACK_BONUS_A): FORCE
	make -C $(FT_STACK_BONUS)

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	cc $(CFLAGS) $(DEPFLAGS) $(INCFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(DEPS) $(OBJ_BONUS) $(DEPS_BONUS)
	make -C $(LIBFT) clean
	make -C $(FT_STACK) clean
	make -C $(FT_STACK_BONUS) clean

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	make -C $(LIBFT) fclean
	make -C $(FT_STACK) fclean
	make -C $(FT_STACK_BONUS) fclean

re: fclean all

-include $(DEPS) $(DEPS_BONUS)

.PHONY: FORCE all clean re fclean bonus
