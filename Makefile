NAME        = push_swap
NAME_BONUS  = checker

CFLAGS      = -Wall -Werror -Wextra
DEPFLAGS    = -MMD -MP
INCFLAGS    = -I./include -I./src/ft_stack/include -I./src/bonus/ft_stack/include -I./libft/include

SRC_DIR     = ./src
OUT_DIR     = ./out
INC_DIR     = ./include

SRC_FILES   = main.c push_swap.c str_to_int.c push_swap_stat.c \
              check_duplicate.c compute_disorder.c merge_sort.c print_bench.c \
              ft_stack/stack_basic.c ft_stack/stack_getter.c \
              ft_stack/stack_push.c ft_stack/stack_rotate.c \
              ft_stack/stack_rrotate.c ft_stack/stack_swap.c \
              sort/complex/complex_sort_small.c sort/complex/complex_sort_util.c \
              sort/complex/complex_sort.c sort/three_sort.c \
              sort/medium/medium_sort.c sort/medium/medium_sort_utils.c \
              sort/util/push_swap_sort_utils.c \
              sort/simple/simple_sort.c sort/simple/align.c \
              sort/simple/simple_sort_cost.c \
              op_buffer/op_buffer.c

SRC_BONUS   = bonus/checker_bonus.c bonus/checker_util_bonus.c \
              push_swap.c str_to_int.c push_swap_stat.c \
              check_duplicate.c compute_disorder.c merge_sort.c print_bench.c \
              bonus/ft_stack/stack_basic_bonus.c \
              bonus/ft_stack/stack_getter_bonus.c \
              bonus/ft_stack/stack_push_bonus.c \
              bonus/ft_stack/stack_rotate_bonus.c \
              bonus/ft_stack/stack_rrotate_bonus.c \
              bonus/ft_stack/stack_swap_bonus.c \
              sort/complex/complex_sort_small.c sort/complex/complex_sort_util.c \
              sort/complex/complex_sort.c sort/three_sort.c \
              sort/medium/medium_sort.c sort/medium/medium_sort_utils.c \
              sort/util/push_swap_sort_utils.c \
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

RM          = rm -rf

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A)
	cc $(CFLAGS) $(OBJ) $(LIBFT_A) $(INCFLAGS) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS) $(LIBFT_A)
	cc $(CFLAGS) $(OBJ_BONUS) $(LIBFT_A) $(INCFLAGS) -o $(NAME_BONUS)

$(LIBFT_A): FORCE
	make -C $(LIBFT)

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	cc $(CFLAGS) $(DEPFLAGS) $(INCFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(DEPS) $(OBJ_BONUS) $(DEPS_BONUS)
	make -C $(LIBFT) clean

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	make -C $(LIBFT) fclean

re: fclean all

-include $(DEPS) $(DEPS_BONUS)

.PHONY: FORCE all clean re fclean bonus
