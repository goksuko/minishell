/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/25 13:40:48 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/09/25 13:40:48 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

bool	is_builtin(char *command);
int		execute_builtin(char **cmds, t_data *shell_data);
int		ft_echo(char **cmds, t_pipex *info);
int		ft_pwd(char **cmds, t_data *shell_data);
int		ft_cd(char **cmds, t_data *shell_data, t_env *env_list);
// // int					ft_env(t_env **env_var);
// // void				ft_exit(t_tree **ast, t_env **env_var); // Remove AST
// // int					exit_atoi(char *str, t_tree **ast, t_env **env_var); // Remove AST
// bool				arg_is_digit(char *str);
// void				free_env(t_env **env_var);

#endif