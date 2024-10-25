# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: vbusekru <vbusekru@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2024/09/03 14:03:42 by vbusekru      #+#    #+#                  #
#    Updated: 2024/10/21 11:15:01 by akaya-oz      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = ./Libft/libft.a

LEXICAL_ANALSYSIS =		tokens.c \
						token_array_list.c \
						define_tokens.c \
						meta_char_check.c \
						tokens_utils.c \
						tokens_utils2.c \
						split_tokens.c \
						token_lst_utils.c \
						token_lst_free.c \
						token_types.c \
						token_types2.c \

SEMANTIC_ANALYSIS = semantic.c \
					cmds_between_pipes.c \
					cmds_from_tokens.c \
					heredoc_semantic.c \
					semantic_utils.c \

BUILTINS = 				builtins.c \
						cd.c \
						echo.c \
						env.c \
						exit_utils.c \
						exit.c \
						pwd.c \
						export.c \
						export_print_env.c \
						export_new_env.c \
						unset.c \

EXECUTE =				child_processes.c \
						children.c \
						execute.c \
						env_list.c \
						env_list_utils.c \
						env_key_funcs.c \
						path.c \
						utils.c \
						utils2.c \

SIGNALS = 				signals.c \

EXPANDER =				single_quotes.c \
						double_quotes.c \
						expand_identifier.c \
						dollar_sign.c \
						dollar_sign_utils.c \
						expander.c \
						expander_utils.c \

SRCS_DIR = sources
OBJS_DIR = objects

SRCS = $(addprefix $(SRCS_DIR)/, \
		errors.c \
		main.c \
		$(addprefix lexical_analysis/, $(LEXICAL_ANALSYSIS)) \
		$(addprefix expander/, $(EXPANDER)) \
		$(addprefix semantic_analysis/, $(SEMANTIC_ANALYSIS)) \
		$(addprefix builtins/, $(BUILTINS)) \
		$(addprefix execute/, $(EXECUTE)) \
		$(addprefix signals/, $(SIGNALS)) \
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
	@mkdir -p $(OBJS_DIR)/semantic_analysis
	@mkdir -p $(OBJS_DIR)/builtins
	@mkdir -p $(OBJS_DIR)/execute
	@mkdir -p $(OBJS_DIR)/signals
	@mkdir -p $(OBJS_DIR)/expander

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

$(OBJS_DIR)/expander/%.o: $(SRCS_DIR)/expander/%.c | $(OBJS_DIR)/expander
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
