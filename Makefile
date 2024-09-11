# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: vbusekru <vbusekru@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/09/03 14:03:42 by vbusekru      #+#    #+#                  #
#    Updated: 2024/09/11 11:01:51 by vbusekru      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = ./Libft/libft.a

LEXICAL_ANALSYSIS =		tokens.c \
						meta_char_check.c \
						tokens_utils.c \
						tokens_utils2.c \
						split_tokens.c \
						token_lst_utils.c \
						token_lst_free.c \
						token_types.c \
						token_types2.c

SYNTAX_ANALSYSIS =		syntax_analysis.c \
						syntax_utils.c \
						redirections.c \
						nodes_utils.c \
						free_tree_list_exit.c \
						syntax_print1.c \
						syntax_print2.c \
						token_types_array.c \

BUILTINS = 				builtins.c \
						pwd.c \
						env.c \
						echo.c \
						exit.c \
						exit_utils.c \
						env_utils.c \

EXECUTE =				execute.c \
						execute_utils.c \
						env_list.c \
						env_list_utils.c \
						env_key_funcs.c \

SIGNALS = 				interactive_signals.c \
						noninteractive_signals.c \

ARGUMENT_EXPANSION =	expand.c \
						expand_utils.c \
						single_quotes.c \

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
		$(addprefix signals/, $(SIGNALS)) \
		$(addprefix argument_expansion/, $(ARGUMENT_EXPANSION)) \
	)

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fPIE -fPIC
SFLAGS = -lreadline

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS_DIR) $(OBJS)
	@echo "Compilation in Progress"
	@$(CC) $(OBJS) $(LIBFT) -o $(NAME) $(SFLAGS) 
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
	@mkdir -p $(OBJS_DIR)/signals
	@mkdir -p $(OBJS_DIR)/argument_expansion

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

$(OBJS_DIR)/signals/%.o: $(SRCS_DIR)/signals/%.c | $(OBJS_DIR)/signals
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/argument_expansion/%.o: $(SRCS_DIR)/argument_expansion/%.c | $(OBJS_DIR)/argument_expansion
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
