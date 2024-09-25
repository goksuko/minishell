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

void	execute_builtins(t_data *shell_data, char **commands);
int		builtins(t_data *shell_data, char *command);
char	*builtin_substr(char *str, int *i);
// int					execute_builtin(t_data *shell_data);
int		ft_pwd(void);
// // int					ft_cd(char **arguments);
// // int					ft_env(t_env **env_var);
int		ft_echo(char *str, t_pipex *info);
// // void				ft_exit(t_tree **ast, t_env **env_var); // Remove AST
// // int					exit_atoi(char *str, t_tree **ast, t_env **env_var); // Remove AST
// bool				arg_is_digit(char *str);
// void				free_env(t_env **env_var);

#endif