NAME = minishell

CC = cc

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

OBJ_DIR = obj

SRC_DIR = src

SRC =	main.c \
		signal.c \
		execution/free.c \
		execution/exit.c \
		execution/exec.c \
		execution/error.c \
		execution/unset.c \
		execution/export.c \
		execution/prompt.c \
		execution/heredoc.c \
		execution/cmd_path.c \
		execution/builtins.c \
		execution/exec_cmd.c \
		execution/set_pipe.c \
		execution/env_utils.c \
		execution/child_prc.c \
		execution/builtins_hand.c \
		parsing/utils.c \
		parsing/env_mod.c \
		parsing/get_cmd.c \
		parsing/io_parse.c \
		parsing/fill_node.c \
		parsing/env_access.c \
		parsing/expansions.c \
		parsing/parse_args.c \
		parsing/ft_cmd_trim.c \
		parsing/handle_array.c \
		parsing/str_trim_all.c \
		parsing/cmd_sub_split.c \
		parsing/validate_syntax.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c
		           
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

READLINE_INCLUDE = -I/opt/vagrant/embedded/include

READLINE_LIB = -L/opt/vagrant/embedded/lib -lreadline

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(READLINE_LIB) -o $@ && \
	echo "\033[32mminishell compiled successfully. Ready to launch 🚀\033[0m" || \
	(echo "\033[31mError while compiling minishell ❌\033[0m" && exit 1)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(READLINE_INCLUDE) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR) $(OBJ_DIR)/parsing $(OBJ_DIR)/execution $(OBJ_DIR)/get_next_line

clean:
	make clean -C $(LIBFT_DIR)
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re