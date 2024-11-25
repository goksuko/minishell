/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 23:09:06 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/11/25 14:33:32 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_directory(const char *path)
{
	struct stat	path_stat;
	bool		is_dir;

	stat(path, &path_stat);
	is_dir = S_ISDIR(path_stat.st_mode);
	return (is_dir);
}

char	*before_exec(char *long_command, t_info *info, char **cmd_matrix)
{
	char	*path;

	path = NULL;
	if (long_command[0] == ' ')
		ft_exit_data_error(info->data, ERROR_NOT_DIR);
	if (cmd_matrix[0])
		path = find_path(info, cmd_matrix[0]);
	if (!path)
	{
		all_messages(info->data, cmd_matrix[0]);
		return (NULL);
	}
	return (path);
}

void	close_fds_from_next_cmds(t_info *info)
{
	int	i;

	i = info->curr_cmd + 1;
	while (i < info->data->nbr_of_cmds)
	{
		if (info->fds[i][0] != -10)
		{
			ms_close(info->data, info->fds[i][0]);
			info->fds[i][0] = -10;
		}
		if (info->fds[i][1] != -10)
		{
			ms_close(info->data, info->fds[i][1]);
			info->fds[i][1] = -10;
		}
		i++;
	}
}

bool	start_exec(t_info *info)
{
	char	**cmd_matrix;
	char	*path;

	path = NULL;
	cmd_matrix = ms_split(info->data, info->data->cmds[info->curr_cmd], ' ');
	update_path(info->data);
	path = before_exec(info->data->cmds[info->curr_cmd], info, cmd_matrix);
	close_fds(info->data, info);
	if (path == NULL)
	{
		free_2d_null(&cmd_matrix);
		free_system(info->data);
		if (info->pipe_read_end != STDIN_FILENO)
			ms_close(info->data, info->pipe_read_end);
		exit(info->data->exit_code);
	}
	close_fds_from_next_cmds(info);
	if (execve(path, cmd_matrix, info->data->envp) == -1)
	{
		all_messages(info->data, cmd_matrix[0]);
		free_2d_null(&cmd_matrix);
		free_system(info->data);
		exit(info->data->exit_code);
	}
	return (true);
}

bool	is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	return (false);
}
