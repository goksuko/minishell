/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 13:40:48 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/04 11:20:04 by vbusekru      ########   odam.nl         */
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

// UNSET
int		ft_unset(char **cmds, t_data *shell_data);
void	unset_env_var(char *key, t_env **env_list);

// EXPORT
int		ft_export(char **cmds, t_data *shell_data);
void	print_sorted_env_list(t_env *env_list);
void	ft_bubble_sort(t_env **temp_env_list);
int		ft_strcmp(char *str1, char *str2);
void	ft_swap(t_env *a, t_env *b);

#endif