NAME = ft_printf_fd.a
LIBFT = ./Libft/objects/*.o

SRCS = \
			ft_char_string.c \
			ft_dec.c \
			ft_long_long.c \
			ft_hex.c \
			ft_printf_fd.c \

SRCS_DIR = sources

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

OBJS_DIR = objects

CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIE

ARC = ar rcs
#r: This option specifies that files should be replaced 
# or added to the archive. If a file with the same name 
# already exists in the archive, it is replaced. If not, it is added.

# c: This option is used to create the archive if it doesn't 
# already exist. If the archive already exists, this option has no effect.

# s: This option is used to update the symbol table of the archive. 
# It is typically used when new object files are added to the archive.

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS) $(LIBFT)
	@echo "Compilation in Progress"
	@$(ARC) $(NAME) $(OBJS)

$(LIBFT):
	@$(MAKE) -s -C ../../Libft

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $^
# % is a wildcard that matches any sequence of characters, 
# and it is used to create a pattern. 
# So, %.o means "any target ending with .o".

# -c: This is a compiler flag that instructs the compiler 
# to generate an object file (.o) without linking. 
# It tells the compiler to stop after the compilation phase.

# $<: This is an automatic variable that represents 
# the first prerequisite (dependency) of the rule. 
# In this context, it represents the source file (%.c).

clean:
	@echo "Cleaning in Progress"
	@rm -rf $(OBJS_DIR)

fclean:clean
	@echo "Cleaning in Progress"
	@rm -f $(NAME) ./a.out

re: fclean all

.PHONY: all clean fclean re
