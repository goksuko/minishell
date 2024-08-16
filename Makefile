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

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/lexical_analysis/%.o: $(SRCS_DIR)/lexical_analysis/%.c | $(OBJS_DIR)/lexical_analysis
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/syntax_analysis/%.o: $(SRCS_DIR)/syntax_analysis/%.c | $(OBJS_DIR)/syntax_analysis
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
	@rm -f ./philo
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -s fclean -C ./Libft
	@echo "***Cleaning Completed***"
	@echo ""

re: fclean all

.PHONY: all clean fclean re
