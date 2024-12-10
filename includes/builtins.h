/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 13:40:48 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/11/25 10:28:46 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

// typedef struct s_cd_data
// {
// 	t_data  *data;
// 	char    *cwd;
// 	char    *old_cwd;
// 	t_env   *env_list;
// } t_cd_data;

bool	is_builtin(char *command);
int		execute_builtin(char **cmds, t_data *data);

// Echo
int		ft_echo(char **cmds, t_info *info);

// PWD
int		ft_pwd(char **cmds, t_data *data);

// CD
int		ft_cd(char **cmds, t_env *env_list, t_data *data);
int		cd_old_pwd(t_env *env_list, t_data *data, t_cd_data *cd_data);
int		cd_home(t_env *env_list, t_data *data, t_cd_data *cd_data);
int		cd_parent_dir(char *cwd, t_data *data, t_cd_data *cd_data);
void	update_env_list(t_env **env_list, char *old_cwd, char *new_cwd, t_cd_data *cd_data);
bool	verify_oldpwd_pwd(t_env *env_list);
// int		ft_cd(char **cmds, t_env *env_list);

// EXIT
int		ft_exit(char **cmds, t_data *data);
int		handle_numeric_arg(char *exit_code, t_data *data);
int		exit_atoi(char *exit_code, t_data *data);
int		get_sign(char c, int *i);
bool	arg_is_digit(char *str);
bool	is_digit(char c);

// ENV
int		ft_env(char **cmds, t_data *data);
void	print_env(t_env *env);

// UNSET
int		ft_unset(char **cmds, t_data *data);
void	unset_env_var(char *key, t_env **env_list);

// EXPORT
int		ft_export(char **cmds, t_data *data);
int		ft_parent_export(char **cmds, t_data *data);
int		set_out_fd(t_data *data);

// EXPORT NO ARGS
void	print_sorted_env_vars(t_env **env, int fd);
t_env	*get_next_var_to_print(t_env *list, t_env *last_printed);
int		get_list_size(t_env *list);
void	print_env_var(t_env *var, int fd);
int		ft_strcmp(const char *s1, const char *s2);

// EXPORT WITH ARGS
int		create_new_env(t_data **data, char *command, char *new_key);
void	add_new_env_node(t_env **env_list, t_env *new_env);
bool	verify_key(char *key, int fd);
int		handle_key(t_data *data,char *command);
bool	check_key_existence(t_data *data, char *key);
int		handle_allocation_error_env(t_data *data);
int		create_new_env_error_handling(t_data *data, char *new_key, char *new_value);
char	*get_new_value(char *command, int start);
char	*extract_key(char *command);
int		update_env_value(t_data *data, char *key, char *command);
int		create_new_env(t_data **data, char *command, char *new_key);

#endif