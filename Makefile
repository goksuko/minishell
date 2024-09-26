# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: vbusekru <vbusekru@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/09/03 14:03:42 by vbusekru      #+#    #+#                  #
#    Updated: 2024/09/26 11:18:05 by akaya-oz      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = ./Libft/libft.a

LEXICAL_ANALSYSIS =		tokens.c \
						define_tokens.c \
						meta_char_check.c \
						tokens_utils.c \
						tokens_utils2.c \
						split_tokens.c \
						token_lst_utils.c \
						token_lst_free.c \
						token_types.c \
						token_types2.c

SEMANTIC_ANALYSIS = semantic.c \
					cmds_from_tokens.c \
					cmds_with_redirs.c \
					semantic_utils.c \
					semantic_utils2.c \

BUILTINS = 			builtins.c \
					# pwd.c \
					# env.c \
					# echo.c \
					# exit.c \
					# exit_utils.c \
					# env_utils.c \

EXECUTE =			child_processes.c \
					children.c \
					define_fds.c \
					execute.c \
					execute_utils.c \
					env_list.c \
					env_list_utils.c \
					env_key_funcs.c \
					path.c \
					utils.c \
					utils2.c \

SIGNALS = 				interactive_signals.c \
						noninteractive_signals.c \

# EXPANSION =				expand.c \
# 						expand_utils.c \
# 						single_quotes.c \
# 						double_quotes.c \
# 						dollar_sign.c \
# 						identifier.c \
# 						redirections.c \

SRCS_DIR = sources
OBJS_DIR = objects

SRCS = $(addprefix $(SRCS_DIR)/, \
		errors.c \
		main.c \
		ft_putstr2_fd.c \
		read_line.c \
		$(addprefix lexical_analysis/, $(LEXICAL_ANALSYSIS)) \
		$(addprefix semantic_analysis/, $(SEMANTIC_ANALYSIS)) \
		$(addprefix builtins/, $(BUILTINS)) \
		$(addprefix execute/, $(EXECUTE)) \
		$(addprefix signals/, $(SIGNALS)) \
	)

# $(addprefix expansion/, $(EXPANSION)) To be moved up again


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
	@mkdir -p $(OBJS_DIR)/semantic_analysis
	@mkdir -p $(OBJS_DIR)/builtins
	@mkdir -p $(OBJS_DIR)/execute
	@mkdir -p $(OBJS_DIR)/signals
	
# @mkdir -p $(OBJS_DIR)/expansion   -To be moved up again

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/lexical_analysis/%.o: $(SRCS_DIR)/lexical_analysis/%.c | $(OBJS_DIR)/lexical_analysis
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/semantic_analysis/%.o: $(SRCS_DIR)/semantic_analysis/%.c | $(OBJS_DIR)/semantic_analysis
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/builtins/%.o: $(SRCS_DIR)/builtins/%.c | $(OBJS_DIR)/builtins
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/execute/%.o: $(SRCS_DIR)/execute/%.c | $(OBJS_DIR)/execute
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/signals/%.o: $(SRCS_DIR)/signals/%.c | $(OBJS_DIR)/signals
	@$(CC) $(CFLAGS) -c $< -o $@

# $(OBJS_DIR)/expansion/%.o: $(SRCS_DIR)/expansion/%.c | $(OBJS_DIR)/expansion
# 	@$(CC) $(CFLAGS) -c $< -o $@

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
