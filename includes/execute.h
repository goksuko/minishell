#ifndef EXECUTE_H
# define EXECUTE_H

// child_processes.c

bool	do_commands(t_data *data, int i);
int	create_children(t_data *data);
// bool	do_child_of_child(t_info *info);
int	do_child_of_child(t_info *info);
int	do_parent_of_child(t_info *info);
pid_t	child_process(t_info *info);

// children.c

int	do_first_child(t_info *info);
int	do_middle_child(t_info *info);
int	do_last_child(t_info *info);
int	handle_child_type(t_info *info);
int		handle_builtin(t_data *data, char **command);

// env_list_utils.c
void	free_prev_nodes(t_env *head);
void	update_shell(t_data *data, t_env **env_list);
void	update_path(t_data *data);
char	*take_path_from_env(t_data *data, t_env **env);
char	*ft_get_env(t_env *env_list, char *value);

// env_list.c
t_env	*ft_envp_node(t_data *data, char *envp_i);
// void    update_envp(t_data *data);
int		find_first_eq(char *envp_i);
t_env	*ft_new_node(t_data *data, char *key, char *value);
int		find_data_if_no_pos(t_data *data, char *envp_i, char **key,
			char **value);
t_env	*create_node(t_data *data, char *envp_i, int pos);
void	free_env(t_env **env_var);

// env_key_funcs.c
bool	key_rules(char c, int index);
int		check_key(t_data *data, char *key);

// execute.c
int		is_file(const char *path);
int	execute_shell(t_data *data);
int	last_exit_code_checks(int exit_code, t_data *data); // to be checked


// Utils functions //
char	*put_main_command(char *command, char space);
int	start_exec(t_info *info);
bool	is_whitespace(char c);

// Path functions //
char	*find_path_helper(t_info *info, char *main_command, char **path_split,
			int i);
char	*find_path(t_info *info, char *main_command);

// utils2.c

int		close_safe(int fd, t_info *info);
int		dup2_safe(int oldfd, int newfd, t_info *info);
void	printf_array(char **array);

#endif