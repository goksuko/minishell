#ifndef EXECUTE_H
# define EXECUTE_H

// child_processes.c

int     create_children(t_data *data);
pid_t   child_process(t_info *info);
pid_t   heredoc_child_process2(t_info *info);

// children.c

void    do_heredoc_child(t_info *info);
void	do_first_child(t_info *info);
void	do_middle_child(t_info *info);
void	do_last_child(t_info *info);

// env_list_utils.c
void	free_prev_nodes(t_env *head);
void	update_shell(t_env **env_list);
void	update_path(t_data *data);
t_env	*ft_envp_node(char *envp_i);
char	*ft_get_env(t_env *env_list, char *value);

// env_list.c
t_env	*ft_envp_node(char *envp_i);
int		find_first_eq(char *envp_i);
t_env	*ft_new_node(char *key, char *value);
int		find_data_if_no_pos(char *envp_i, char **key, char **value);
t_env	*create_node(char *envp_i, int pos);
void	free_env(t_env **env_var);

// env_key_funcs.c
bool	key_rules(char c, int index);
int		check_key(char *key);


// execute_utils.c
int		is_file(const char *path);

// execute.c

void	execute_shell(t_data *data);

// Utils functions //
char	*put_main_command(char *command, char space);
void	start_exec(t_info *info);
void	*free_matrix(char **matrix);
void	close_info(t_info *info, char **matrix);
bool	is_whitespace(char c);
pid_t	heredoc_child_process(t_info *info, char **cmd_matrix, char *path);

// Path functions //
char	*find_path(t_info *info, char *main_command, char *path_from_getenv);

// utils2.c

int		close_safe(int fd, t_info *info);
int		dup2_safe(int oldfd, int newfd, t_info *info);
void	printf_array(char **array);


#endif