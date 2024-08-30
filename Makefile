NAME = minishell
LIBFT = ./Libft/libft.a

LEXICAL_ANALSYSIS = tokens.c \
					meta_char_check.c \
					tokens_utils.c \
					tokens_utils2.c \
					split_tokens.c \
					token_lst_utils.c \
					token_lst_free.c \
					token_types.c \
					token_types2.c

SYNTAX_ANALSYSIS = syntax_analysis.c \
					syntax_utils.c \
					redirections.c \
					nodes_utils.c \
					free_tree_list_exit.c \
					syntax_print1.c \
					syntax_print2.c \

BUILTINS = 			builtins.c \
					pwd.c \
					env.c \
					echo.c \
					exit.c \
					env_utils.c \

EXECUTE =			execute.c \
					execute_utils.c \

SRCS_DIR = sources
OBJS_DIR = objects

SRCS = $(addprefix $(SRCS_DIR)/, \
		errors.c \
		main.c \
		utils.c \
		utils2.c \
		ft_putstr2_fd.c \
		path.c \
		pipex.c \
		read_line.c \
		$(addprefix lexical_analysis/, $(LEXICAL_ANALSYSIS)) \
		$(addprefix syntax_analysis/, $(SYNTAX_ANALSYSIS)) \
		$(addprefix builtins/, $(BUILTINS)) \
		$(addprefix execute/, $(EXECUTE)) \
	)

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fPIE -fPIC
SFLAGS = -lreadline

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS_DIR) $(OBJS)
	@echo "Compilation in Progress"
	@$(CC) $(SFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo ""
	@echo "********Completed********"

$(LIBFT):
	@$(MAKE) -s -C ./Libft

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/lexical_analysis
	@mkdir -p $(OBJS_DIR)/syntax_analysis
	@mkdir -p $(OBJS_DIR)/builtins
	@mkdir -p $(OBJS_DIR)/execute

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/lexical_analysis/%.o: $(SRCS_DIR)/lexical_analysis/%.c | $(OBJS_DIR)/lexical_analysis
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/syntax_analysis/%.o: $(SRCS_DIR)/syntax_analysis/%.c | $(OBJS_DIR)/syntax_analysis
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/builtins/%.o: $(SRCS_DIR)/builtins/%.c | $(OBJS_DIR)/builtins
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/execute/%.o: $(SRCS_DIR)/execute/%.c | $(OBJS_DIR)/execute
	@$(CC) $(CFLAGS) -c $< -o $@


clean:
	@echo "Cleaning in Progress"
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -s clean -C ./Libft
	@echo "Cleaning Completed"

fclean:
	@echo "Cleaning in Progress"
	@rm -f $(NAME) $(BONUS_NAME)
	@rm -f ./a.out
	@rm -f ./sources/a.out
	@rm -f ./minishell
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -s fclean -C ./Libft
	@echo "***Cleaning Completed***"
	@echo ""

re: fclean all

.PHONY: all clean fclean re
