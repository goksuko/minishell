/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/29 21:30:01 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/11/10 19:29:28 by vbusekru      ########   odam.nl         */
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
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

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
	char			**expanded_cmds;
	struct s_info	*info;
	struct s_env	*env_list;
	struct s_token	*tokens;
}					t_data;

typedef struct s_info
{
	int				pipefd[2];
	int				fds[100][2];
	int				fd_in;
	int				fd_out;
	char			*infile;
	char			*outfile;
	int				curr_cmd;
	int				here_doc_cmd;
	char			*limiter;
	char			*path;
	int				pipe_read_end;
	struct s_data	*data;
}					t_info;

typedef struct s_env
{
	char *key;   //  in the environment variable PATH=/usr/bin, PATH is the key.
	char *value; // In the PATH=/usr/bin example, /usr/bin is the value
	struct s_env	*next;
}					t_env;

# include "lexer_sem.h"
# include "expander.h"
# include "builtins.h"
# include "execute.h"
# include "errors_free_exit.h"
// Otherwise the program cannot be compiled if it is higher up because it needs the data struct
# define SUCCESS 0

// main.c

char				*rl_gets(void);
void				init_data(t_info *info, t_data *data, char **envp);
void	make_initial_path_checks(t_data *data, char **envp);
bool				minishell_routine(t_data *data);

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


// Signals
void				handle_signals(int process);
void				handle_child_sigquit(int signal);
void				handle_child_sigint(int signal);
void				handle_parent_sigint(int signal);

void				set_signals(t_data *data);
void				unset_signals(void);
void				signals_for_kids(void);
void				signal_int_handler(int sig);

void    ms_dup2(t_data *data, int old_fd, int new_fd);
void    ms_close(t_data *data, int fd);
int		ms_open(t_data *data, char *file, int flags, int mode);
void    ms_pipe(t_data *data, int *pipefd);
int		ms_fork(t_data *data);
void    ms_unlink(t_data *data, char *file);
void	**ms_calloc(t_data *data, size_t nmemb, size_t size);
char	*ms_strjoin(t_data *data, const char *s1, const char *s2);
char	*ms_strdup(t_data *data, const char *s);
char	**ms_split(t_data *data, char const *s, char c);
#endif
