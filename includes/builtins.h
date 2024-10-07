/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 13:40:48 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/07 09:36:46 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

bool	is_builtin(char *command);
int		execute_builtin(char **cmds, t_data *shell_data);

// Echo
int		ft_echo(char **cmds, t_pipex *info);

// PWD
int		ft_pwd(char **cmds, t_data *shell_data);

// CD
int		ft_cd(char **cmds, t_env *env_list);

// EXIT
void	ft_exit(char **cmds, t_data *shell_data);
void	handle_numeric_arg(char *exit_code, t_data *shell_data);
int		exit_atoi(char *exit_code, t_data *shell_data);
int		get_sign(char c, int *i);
bool	arg_is_digit(char *str);
bool	is_digit(char c);

// ENV
int		ft_env(char **cmds, t_data *shell_data);
void	print_env(t_env *env);

// UNSET
int		ft_unset(char **cmds, t_data *shell_data);
void	unset_env_var(char *key, t_env **env_list);

// EXPORT
int		ft_export(char **cmds, t_data *shell_data);

// EXPORT NO ARGS
void	print_sorted_env_vars(t_env **env, int fd);
t_env 	*get_next_var_to_print(t_env *list, t_env *last_printed);
int		get_list_size(t_env *list);
void	print_env_var(t_env *var, int fd);

// EXPORT WITH ARGS
void	create_new_env(t_data **shell_data, char *command);
void	add_new_env_node(t_env **env_list, t_env *new_env);
char	*extract_key(char *command);
bool	verify_key(char *key, int fd);
void	handle_allocation_error_env(t_data **shell_data);
char	*get_new_value(char *command, int start);
char	*get_new_key(char *command);

#endif