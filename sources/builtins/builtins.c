/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 13:45:43 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/11/18 11:06:32 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtin(char **cmds, t_data *data)
{
	int	return_value;
	int	cmd_len;

	return_value = -1;
	// printf("----EXECUTE BUILTIN----\n"); // DEBUGGING PURPOSES!
	// printf_array(cmds); // DEBUGGING PURPOSES!
	cmd_len = ft_strlen(cmds[0]);
	if (cmd_len == 4 && (ft_strncmp(cmds[0], "echo", 4) == 0
			|| ft_strncmp(cmds[0], "ECHO", 4) == 0))
		return_value = ft_echo(cmds + 1, data->info);
	else if (cmd_len == 2 && ft_strncmp(cmds[0], "cd", 2) == 0)
		return_value = ft_cd(cmds + 1, data->env_list, data);
	else if (cmd_len == 3 && (ft_strncmp(cmds[0], "pwd", 3) == 0
			|| ft_strncmp(cmds[0], "PWD", 3) == 0))
		return_value = ft_pwd(cmds + 1, data);
	if (cmd_len == 6 && ft_strncmp(cmds[0], "export", 6) == 0)
		return_value = ft_export(cmds + 1, data);
	else if (cmd_len == 5 && ft_strncmp(cmds[0], "unset", 5) == 0)
		return_value = ft_unset(cmds + 1, data);
	else if (cmd_len == 3 && (ft_strncmp(cmds[0], "env", 3) == 0
			|| ft_strncmp(cmds[0], "ENV", 3) == 0))
		return_value = ft_env(cmds + 1, data);
	else if (cmd_len == 4 && ft_strncmp(cmds[0], "exit", 4) == 0)
		return_value = ft_exit(cmds + 1, data);
	// printf("----EXECUTE BUILTIN DONE---\n");
	return (return_value);
}

// int	execute_parent_builtin(char **cmds, t_data *data) // to be called in execution
// {
// 	int	return_value;
// 	int	cmd_len;

// 	return_value = -1;
// 	cmd_len = ft_strlen(cmds[0]);
// 	if (cmd_len == 2 && ft_strncmp(cmds[0], "cd", 2) == 0)
// 		return_value = ft_cd(cmds + 1, data->env_list, data);
// 	else if (cmd_len == 6 && ft_strncmp(cmds[0], "export", 6) == 0)
// 		return_value = ft_parent_export(cmds + 1, data);
// 	else if (cmd_len == 5 && ft_strncmp(cmds[0], "unset", 5) == 0)
// 		return_value = ft_unset(cmds + 1, data);
// 	// else if (cmd_len == 4 && ft_strncmp(cmds[0], "exit", 4) == 0)
// 	// 	return_value = ft_exit(cmds + 1, data); // but exit code does need to be updated. to be checked with goksu
// 	printf("---EXECUTE PARENT BUILT IN DONE---\n");
// 	return (return_value);
// }

bool	is_builtin(char *command)
{
	int	cmd_len;

	if (command == NULL)
		return (false);
	cmd_len = ft_strlen(command);
	if (cmd_len == 4 && (ft_strncmp(command, "echo", 4) == 0
			|| ft_strncmp(command, "ECHO", 4) == 0))
		return (true);
	if (cmd_len == 2 && ft_strncmp(command, "cd", 2) == 0)
		return (true);
	if (cmd_len == 3 && (ft_strncmp(command, "pwd", 3) == 0
			|| ft_strncmp(command, "PWD", 3) == 0))
		return (true);
	if (cmd_len == 6 && ft_strncmp(command, "export", 6) == 0)
		return (true);
	if (cmd_len == 5 && ft_strncmp(command, "unset", 5) == 0)
		return (true);
	if (cmd_len == 3 && (ft_strncmp(command, "env", 3) == 0
			|| ft_strncmp(command, "ENV", 3) == 0))
		return (true);
	if (cmd_len == 4 && ft_strncmp(command, "exit", 4) == 0)
		return (true);
	return (false);
}
