// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   utils.c                                            :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2024/05/16 13:34:42 by akaya-oz      #+#    #+#                 */
// /*   Updated: 2024/09/06 16:19:04 by akaya-oz      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../includes/minishell.h"

char	*before_exec(char *long_command, t_info *info, char **cmd_matrix)
{
	char	*path;

	path = NULL;
	if (long_command[0] == ' ')
		ft_exit_data_error(info->data, ERROR_NOT_DIR);
	if (cmd_matrix[0])
		path = find_path(info, cmd_matrix[0]);
	else  /////////////////////////////////////////////////////////////////// CHECK HERE
	{
		ft_printf_fd(STDERR_FILENO, "bash: %s: Permission denied\n", info->outfile);
		info->data->exit_code = 126;
		free_data(&info->data); //free_system
		// exit(126);
	}
	if (!path)
	{
		ft_putstr3_fd("command not found: ", cmd_matrix[0], "\n", STDERR_FILENO);
		free_data(&info->data); //free_system
		info->data->exit_code = 127;
		// exit(127);
	}
	printf("path before exec: %s\n", path);
	return (path);
}

void	start_exec(t_info *info)
{
	char	**cmd_matrix;
	char	*path;

	path = NULL;
	cmd_matrix = ft_split(info->data->cmds[info->curr_cmd], ' ');
	if (!cmd_matrix || errno == ENOMEM)
		ft_exit_data_perror(info->data, ERROR_ALLOCATION, "cmd_matrix in start_exec");
	update_path(info->data);
	path = before_exec(info->data->cmds[info->curr_cmd], info, cmd_matrix);
	if (execve(path, cmd_matrix, info->data->envp) == -1)
		ft_exit_data_perror(info->data, ERROR_EXECVE, "execve in start_exec");

}

char	*put_main_command(char *command, char space)
{
	char	*temp;
	int		i;

	i = 0;
	while (command[i] != space && command[i] != '\0')
		i++;
	temp = (char *)ft_calloc(sizeof(char), (i + 1));
	if (!temp || errno == ENOMEM)
		ft_exit_perror(ERROR_ALLOCATION, "temp in put_main_command");
	i = 0;
	while (command[i] != space && command[i] != '\0')
	{
		temp[i] = command[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

bool	is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	return (false);
}
