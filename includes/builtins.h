/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 13:40:48 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/01 16:01:11 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

bool	is_builtin(char *command);
int		execute_builtin(char **cmds, t_data *shell_data);
int		ft_echo(char **cmds, t_pipex *info);
int		ft_pwd(char **cmds, t_data *shell_data);
int		ft_cd(char **cmds, t_data *shell_data, t_env *env_list);
void	ft_exit(char **cmds, t_data *shell_data);
void	handle_numeric_arg(char *exit_code, t_data *shell_data);
int		exit_atoi(char *exit_code, t_data *shell_data);
int		get_sign(char c, int *i);
bool	arg_is_digit(char *str);
bool	is_digit(char c);

#endif