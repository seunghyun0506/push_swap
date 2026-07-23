NAME        = push_swap
NAME_BONUS  = checker

CFLAGS      = -Wall -Werror -Wextra
DEPFLAGS    = -MMD -MP
INCFLAGS        = -I./include -I./src/ft_stack/include -I./libft/include
INCFLAGS_BONUS  = -I./bonus/include -I./libft/include

SRC_DIR     = ./src
BONUS_DIR   = ./bonus
OUT_DIR     = ./out
BONUS_OUT_DIR = ./bonus/out
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
              sort/util/op_stack_push.c sort/util/op_stack_rotate.c \
              sort/util/op_stack_rrotate.c sort/util/op_stack_swap.c \
              sort/simple/simple_sort.c sort/simple/align.c \
              sort/simple/simple_sort_cost.c \
              op_buffer/op_buffer.c

BONUS_FILES = checker_bonus.c checker_util_bonus.c \
              push_swap_bonus.c str_to_int_bonus.c \
              push_swap_stat_bonus.c check_duplicate_bonus.c \
              ft_stack/stack_basic_bonus.c \
              ft_stack/stack_getter_bonus.c \
              ft_stack/stack_push_bonus.c \
              ft_stack/stack_rotate_bonus.c \
              ft_stack/stack_rrotate_bonus.c \
              ft_stack/stack_swap_bonus.c

SRC         = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ         = $(addprefix $(OUT_DIR)/, $(SRC_FILES:.c=.o))
DEPS        = $(OBJ:.o=.d)

SRC_BONUS   = $(addprefix $(BONUS_DIR)/, $(BONUS_FILES))
OBJ_BONUS   = $(addprefix $(BONUS_OUT_DIR)/, $(BONUS_FILES:.c=.o))
DEPS_BONUS  = $(OBJ_BONUS:.o=.d)

LIBFT       = ./libft
LIBFT_A     = ./libft/libft.a

RM          = rm -rf

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A)
	cc $(CFLAGS) $(OBJ) $(LIBFT_A) $(INCFLAGS) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS) $(LIBFT_A)
	cc $(CFLAGS) $(OBJ_BONUS) $(LIBFT_A) $(INCFLAGS_BONUS) -o $(NAME_BONUS)

$(LIBFT_A):
	make -C $(LIBFT)

$(BONUS_OUT_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(dir $@)
	cc $(CFLAGS) $(DEPFLAGS) $(INCFLAGS_BONUS) -c $< -o $@

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	cc $(CFLAGS) $(DEPFLAGS) $(INCFLAGS) -c $< -o $@

clean:
	$(RM) $(OUT_DIR) $(BONUS_OUT_DIR)
	make -C $(LIBFT) clean

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	make -C $(LIBFT) fclean

re: fclean all

-include $(DEPS) $(DEPS_BONUS)

.PHONY: all clean re fclean bonus
