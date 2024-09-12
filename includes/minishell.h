/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/29 21:30:01 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/09/12 17:00:06 by vbusekru      ########   odam.nl         */
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
# include "lexer.h"
# include "syntax.h"
# include <termios.h>

# define SUCCESS 0

typedef enum e_error
{
	NO_ERROR,
	ERROR_PERM = 1,
	ERROR_ARGUMENT_COUNT,
	ERROR_TOO_MAY_ARGS,
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

typedef struct s_pipex
{
	int				pipefd[2];
	int				fds[100][2];
	int				fd_in;
	int				fd_out;
	char			*infile;
	char			*outfile;
	int				nbr_of_cmds;
	int				curr_cmd;
	char			**cmds;
	char			*path;
	char			*path_from_getenv;
	struct s_data	*data;
}					t_pipex;

typedef struct s_data
{
	char			**cmds;
	char			*line;
	char			**envp;
	char			*path;
	int				exit_code;
	int				nbr_of_cmds;
	int				nbr_of_pipes;
	char			**cmds_for_pipe;
	struct s_pipex	*info;
	struct s_env	*env_list;
	struct s_tree	*ast;
	struct s_token	*tokens;
}					t_data;

typedef struct s_env
{
	char			*key; //  in the environment variable PATH=/usr/bin, PATH is the key.
	char			*value; // In the PATH=/usr/bin example, /usr/bin is the value
	struct s_env	*next;
}					t_env;

// main.c

int					check_pipe(char *line);
int					find_path_index(char **envp);
char				*rl_gets(void);

// errors.c

int					ft_print_error(t_error code);
void				ft_exit_perror(t_error code, char *s);
void				ft_exit_str_fd(t_error code, int fd);
void				ft_exit_str_free_fd(t_error code, char *str, int fd);
void				free_system(t_data *data);
void				ft_exit_data_perror(t_data *data, t_error code, char *s);
void				ft_exit_data_error(t_data *data, t_error code);
void				ft_close_exit_perror(t_pipex *info, char **matrix,
						t_error code, char *s);

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

// Utils functions //
char				*put_main_command(char *command, char space);
void				start_exec(t_pipex *info);
void				*free_matrix(char **matrix);
void				close_pipex(t_pipex *info, char **matrix);
bool				is_whitespace(char c);


// Path functions //
char				*find_path(t_pipex *info, char *main_command, char *path_from_getenv);

// Ft_putstr2_fd functions //
void				ft_putstr2_fd(char *s1, char *s2, int fd);
void				ft_putstr3_fd(char *s1, char *s2, char *s3, int fd);

// utils2.c

int					close_safe(int fd, t_pipex *info);
int					dup2_safe(int oldfd, int newfd, t_pipex *info);

// pipex.c

int					pipex(t_data *data);
int					is_file(const char *path);
int 	is_file(const char *path);
pid_t	child_process(t_pipex *info);
pid_t	last_child_process(t_pipex *info);
int		create_children(t_data *data);
void	initialize_cmds(t_data *data, t_pipex *info);
char	*find_infile(t_pipex *info);
char	*find_outfile(t_pipex *info);


// Builtins
bool				is_builtin(char *command);
int					execute_builtin(t_data *shell_data);
int					ft_pwd(void);
// int					ft_cd(char **arguments);
// int					ft_env(t_env **env_var);
int					ft_echo(char **arguments);
void				ft_exit(t_tree **ast, t_env **env_var);
int					exit_atoi(char *str, t_tree **ast, t_env **env_var);
bool				arg_is_digit(char *str);
void				free_env(t_env **env_var);

// Execute
void				execute_shell(t_data *shell_data);
// t_env				*init_env_var(void);
void				execute_command(t_data *shell_data);
void	initialize_info(t_pipex *info, t_data *shell_data);


// execute_utils.c
void				free_tree_env(t_tree **ast, t_env **env_var);

// env_list_utils.c
void	free_prev_nodes(t_env *head);
void	update_shell(t_env **env_list);
void	update_path(t_data *shell_data);
t_env	*ft_envp_node(char *envp_i);

// env_list.c
t_env	*ft_envp_node(char *envp_i);
int		find_first_eq(char *envp_i);
t_env	*ft_new_node(char *key, char *value);
int		find_data_if_no_pos(char *envp_i, char **key, char **value);
t_env	*create_node(char *envp_i, int pos);

// env_key_funcs.c
bool	key_rules(char c, int index);
int		check_key(char *key);

// Signals
void	interactive_signals(void);
void	noninteractive_signals(void);
void	handle_siquit_interactive(int signal);
void	handle_siquit_noninteractive(int signal);
void	handle_sigint_interactive(int signal);
void	handle_sigint_noninteractive(int signal);
void	not_output_signal_keys();
void	output_signal_keys();

// Argument expansion
void	expansion(t_data **shell_data, t_tree **node);
void	expand_arguments(t_data **shell_data, t_tree **node);
void	init_expanded_arguments(t_tree **node);
char	*remove_quotation_marks(char *argument);
char	*s_quotes(char *argument);
bool	dollar_sign_check(char *argument);
char	*d_quotes(t_data **shell_data, char *argument);
char	*create_expanded_str(char *str, int i, char *expanded_str, int chars_to_remove);
char	*handle_dollar_sign(t_data **shell_data, char *str);

#endif
