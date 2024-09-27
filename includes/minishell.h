/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/29 21:30:01 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/09/25 12:00:40 by vbusekru      ########   odam.nl         */
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
	char			**expanded_cmds; // to be freed properly!!
	struct s_pipex	*info;
	struct s_env	*env_list;
	struct s_token	*tokens;
}					t_data;

typedef enum e_error
{
	NO_ERROR,
	ERROR_PERM = 1,
	ERROR_ARGUMENT_COUNT,
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
	char			*special_command;
	char 			*limiter;
	char			*path;
	char			*path_from_getenv;
	int				pipe_read_end;
	struct s_data	*data;
}					t_pipex;

typedef struct s_env
{
	char			*key; //  in the environment variable PATH=/usr/bin, PATH is the key.
	char			*value; // In the PATH=/usr/bin example, /usr/bin is the value
	struct s_env	*next;
}					t_env;


# include "lexer.h" // Otherwise the program cannot be compiled if it is higher up because it needs to data strut
# include "builtins.h"
# define SUCCESS 0

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
void				printf_array(char **array);

// pipex.c

// int 	is_file(const char *path);
pid_t	child_process(t_pipex *info);
pid_t	last_child_process(t_pipex *info);
int		create_children(t_data *data);
// void	initialize_cmds(t_data *data, t_pipex *info);
char	*find_infile(t_pipex *info);
char	*find_outfile(t_pipex *info);

// child_processes.c

pid_t	child_process(t_pipex *info);
int		create_children(t_data *data);

// children.c

void				do_first_child(t_pipex *info);
void				do_middle_child(t_pipex *info);
void				do_last_child(t_pipex *info);

// define_fds.c

void define_fd_in_out(t_pipex *info);
void define_redir_in(t_pipex *info, char *file_name);
void define_redir_out(t_pipex *info, char *file_name);
void define_redir_append(t_pipex *info, char *file_name);
void define_redir_heredoc(t_pipex *info, char *limiter);

// Execute
void				execute_shell(t_data *shell_data);
// t_env				*init_env_var(void);
// void				execute_command(t_data *shell_data);
int					pipes(t_data *data);
// void	initialize_info(t_pipex *info, t_data *shell_data);
void				execute_node(t_data *shell_data);

// execute_utils.c
int					is_file(const char *path);

// env_list_utils.c
void	free_prev_nodes(t_env *head);
void	update_shell(t_env **env_list);
void	update_path(t_data *shell_data);
t_env	*ft_envp_node(char *envp_i);
t_env	*ft_get_env(t_env *env_list, char *value);

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
// void	begin_expansion(t_data *shell_data);
// void	expansion(t_data **shell_data, t_tree **node, int *i);
// char	*expand_arguments(t_data **shell_data, t_tree **node);
// void	init_expanded_cmds(t_data **shell_data);
// char	*create_arg_str(t_data **shell_data, t_tree **node, char *expanded_args);
// char	*add_redirection_to_cmd(t_data **shell_data, \
// 		t_tree **node, char *expanded_args);
// char	*add_redirection(t_data **shell_data, t_tree **node);
// char	*redir_value(t_redirection_type type);
// char	*expand_argument(t_data **shell_data, t_tree *node, int i);
// char	*remove_quotation_marks(char *argument);
// char	*s_quotes(t_data **shell_data, char *argument);
// bool	dollar_sign_check(char *argument);
// char	*d_quotes(t_data **shell_data, char *argument);
// char	*handle_dollar_sign(t_data **shell_data, char *str);
// char	*expand_identifier(t_data **shell_data, char *argument);
// char	*ft_strjoin_c(char const *s1, char c);
// char	*add_space_to_str(t_data **shell_data, char *str);
// int		ast_size(t_tree *ast);

// Free shell data
void	free_shell_data(t_data **data);

//semantic.c
void	semantic_analysis(t_data *shell_data);

//semantic_utils.c
int		find_pipe_count(char *line);
void	initialize_cmds(t_data *data, t_pipex *info);
void	initialize_info(t_pipex *info, t_data *data);
char 	**clean_spaces(char **matrix);

//semantic_utils2.c
char *clean_redirects(char *long_command);

#endif
