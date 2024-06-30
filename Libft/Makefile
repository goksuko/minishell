NAME = libft.a
FT_PRINTF_FD = ./ft_printf_fd/objects/*.o
FT_UTILS = ./ft_utils/objects/*.o

SRCS = \
			ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_itoa.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_split.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			get_next_line.c \
			get_next_line_utils.c
#			ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstsize.c

SRCS_DIR = Libft_sources

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

OBJS_DIR = objects

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(FT_PRINTF_FD) $(FT_UTILS) $(OBJS_DIR) $(OBJS)
	@echo "Compilation in Progress"
	@ar rcs $(NAME) $(OBJS) $(FT_PRINTF_FD) $(FT_UTILS)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(FT_PRINTF_FD):
	@$(MAKE) -s -C ./ft_printf_fd

$(FT_UTILS):
	@$(MAKE) -s -C ./ft_utils

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $^

clean:
	@echo "Cleaning in Progress"
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -s clean -C ./ft_printf_fd
	@$(MAKE) -s clean -C ./ft_utils

fclean:clean
	@echo "Cleaning in Progress"
	@rm -f $(NAME) ./a.out
	@$(MAKE) -s fclean -C ./ft_printf_fd
	@$(MAKE) -s fclean -C ./ft_utils

re: fclean all

.PHONY: all clean fclean re