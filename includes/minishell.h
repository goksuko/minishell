/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/29 21:30:01 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/17 14:45:51 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/ft_printf_fd/includes/ft_printf_fd.h"
# include "../Libft/ft_utils/includes/ft_utils.h"
# include "../Libft/includes/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <string.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/stat.h>
# include <termios.h>

# define PARENT 1
# define CHILD 2
# define HEREDOC 3

typedef struct s_data
{
	char			**cmds;
	char			*line;
	char			**envp;
	char			*path;
	int				exit_code;
	int				nbr_of_cmds;
	int				nbr_of_pipes;
	int				nbr_of_tokens;
	char			**expanded_cmds; // to be freed properly!!
	struct s_info	*info;
	struct s_env	*env_list;
	// struct s_tree	*ast;
	struct s_token	*tokens;
}					t_data;

typedef enum e_error
{
	NO_ERROR,
	ERROR_PERM = 1,
	ERROR_ARGUMENT_COUNT,
	ERROR_NO_ENVP,
	ERROR_TOO_MANY_ARGS,
	ERROR_NUMERIC_ARG,
	ERROR_INVALID_ARGUMENTS,
	ERROR_ALLOCATION,
	ERROR_FILE_OPEN,
	ERROR_NULL_PATH,
	ERROR_CMD_NOT_FOUND,
	ERROR_PIPE,
	ERROR_FORK,
	ERROR_CLOSE,
	ERROR_DUP2,
	ERROR_EXECVE,
	ERROR_HOME_DIR,
	ERROR_PARENT_DIR,
	ERROR_OLDPWD,
	ERROR_NO_FILE_DIR,
	ERROR_QUOTE,
	ERROR_WRONG_CHAR,
	ERROR_FILE_NOT_FOUND,
	ERROR_META,
	ERROR_SYNTAX,
	ERROR_EMPTY_LINE,
	UNDEFINED_ERROR,
	ERROR_INVALID_IDENTIFIER,
	ERROR_NOT_DIR = 127,
}					t_error;

typedef struct s_info
{
	int				pipefd[2];
	int				fds[100][2];
	int				fd_in;
	int				fd_out;
	char			*infile;
	char			*outfile;
	// int				nbr_of_cmds;
	int				curr_cmd;
	int				here_doc_cmd;
	// char			**cmds;
	// char			*special_command;
	char 			*limiter;
	char			*path;
	char			*path_from_getenv;
	int				pipe_read_end;
	struct s_data	*data;
}					t_info;

typedef struct s_env
{
	char			*key; //  in the environment variable PATH=/usr/bin, PATH is the key.
	char			*value; // In the PATH=/usr/bin example, /usr/bin is the value
	struct s_env	*next;
}					t_env;


# include "lexer_sem.h" // Otherwise the program cannot be compiled if it is higher up because it needs to data strut
# include "builtins.h"
# include "expander.h"
# include "execute.h"
# define SUCCESS 0

// main.c

int					check_pipe(char *line);
int					find_path_index(char **envp);
char				*rl_gets(void);
bool				minishell_routine(t_data *data, char *line);

// errors.c

int					ft_print_error(t_error code);
void				ft_exit_perror(t_error code, char *s);
void				ft_exit_str_fd(t_error code, int fd);
void				ft_exit_str_free_fd(t_error code, char *str, int fd);
void				free_system(t_data *data);
void				ft_exit_data_perror(t_data *data, t_error code, char *s);
void				ft_exit_data_error(t_data *data, t_error code);
void				ft_close_exit_perror(t_info *info, t_error code, char *s);
void				close_info(t_info *info);
void				free_data(t_data **data);


// Libft functions //

size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strdup(const char *s);
char				**ft_split(char const *s, char c);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
void				ft_putstr_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
void				*ft_calloc(size_t nmemb, size_t size);


// Ft_putstr2_fd functions //
void				ft_putstr2_fd(char *s1, char *s2, int fd);
void				ft_putstr3_fd(char *s1, char *s2, char *s3, int fd);

// info.c

pid_t	child_process(t_info *info);
int		create_children(t_data *data);

// Signals
void	handle_signals(int process);
void	handle_child_sigquit(int signal);
void	handle_child_sigint(int signal);
void	handle_parent_sigint(int signal);



#endif
