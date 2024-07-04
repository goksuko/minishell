NAME = minishell
LIBFT = ./Libft/libft.a

SRCS = \
		errors.c \
		main.c \
		utils.c \
		utils2.c \
		ft_putstr2_fd.c \
		path.c \
		pipex.c \


SRCS_DIR = sources

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

OBJS_DIR = objects

CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -g

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS_DIR) $(OBJS)
	@echo "Compilation in Progress"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo ""
	@echo "********Completed********"
#	$(CC) $(LFLAGS) -g -fsanitize=address $(OBJS_1) $(OBJS_2) $(MINILIBX) $(FT_PRINTF) $(LIBFT) -o $(NAME)
#	$(CC) $(CFLAGS) $(LFLAGS) -g -fPIE -fPIC -fsanitize=address $(OBJS_1) $(OBJS_2) $(MINILIBX) $(FT_PRINTF) $(LIBFT) -o $(NAME)
#	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS_1) $(OBJS_2) $(MINILIBX) $(FT_PRINTF) $(LIBFT) -o $(NAME)
#	$(CC) $(CFLAGS) $(LFLAGS) -g -fPIE -fPIC $(OBJS_1) $(OBJS_2) $(MINILIBX) $(FT_PRINTF) $(LIBFT) -o $(NAME)
#	$(CC) $(CFLAGS) $(LFLAGS) -g $(OBJS_1) $(OBJS_2) $(MINILIBX) $(FT_PRINTF) $(LIBFT) -o $(NAME)
#	$(CC) $(LFLAGS) -g $(OBJS_1) $(OBJS_2) $(MINILIBX) $(FT_PRINTF) $(LIBFT) -o $(NAME)

$(LIBFT):
	@$(MAKE) -s -C ./Libft

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $^

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
