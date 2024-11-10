/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 23:09:06 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/11/10 22:49:22 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool is_directory(const char *path)
{
    struct stat path_stat;

   	stat(path, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}

char	*before_exec(char *long_command, t_info *info, char **cmd_matrix)
{
	char	*path;

	path = NULL;
	if (long_command[0] == ' ')
		ft_exit_data_error(info->data, ERROR_NOT_DIR);
	if (cmd_matrix[0])
		path = find_path(info, cmd_matrix[0]);
	// else
	// /////////////////////////////////////////////////////////////////// CHECK HERE
	// {
	// 	ft_printf_fd(STDERR_FILENO, "bash: %s: Permission denied\n",
	// 		info->outfile);
	// 	info->data->exit_code = 126;
	// 	free_data(&info->data); // free_system
	// 							// exit(126);
	// }
	if (!path)
	{
		// if (cmd_matrix[0][0] == '.' && cmd_matrix[0][1] == '/')
		// {
		// 	ft_putstr3_fd(cmd_matrix[0], ": Permission denied", "\n",
		// 		STDERR_FILENO);
		// 	info->data->exit_code = 126;
		// }
		// else if (cmd_matrix[0][0] == '/')
		if (cmd_matrix[0][0] == '/')
		{
			ft_putstr3_fd(cmd_matrix[0], ": No such file or directory", "\n",
				STDERR_FILENO);
			info->data->exit_code = 127;		
		}
		// else if (is_file(cmd_matrix[0]))
		// if (is_file(cmd_matrix[0]))
		// {
		// 	ft_putstr3_fd(cmd_matrix[0], ": Nodfhasldfa such file or directory", "\n",
		// 		STDERR_FILENO);
		// 	info->data->exit_code = 127;		
		// }
		// else if (is_directory(cmd_matrix[0]))
		else if (cmd_matrix[0][0] == '.' && cmd_matrix[0][1] == '/')
		{
			if (access(cmd_matrix[0], F_OK))
			{
				if (access(cmd_matrix[0], X_OK) == 0)
				{
					ft_putstr3_fd(cmd_matrix[0], ": Permission denied", "\n",
						STDERR_FILENO);
					info->data->exit_code = 126;
				}
				else
				{
					ft_putstr3_fd(cmd_matrix[0], ": No such file or directory", "\n",
						STDERR_FILENO);
					info->data->exit_code = 127;		
				}
			}
			else
			{
				if (is_directory(cmd_matrix[0]))
				{
					ft_putstr3_fd(cmd_matrix[0], ": Is a directory", "\n",
						STDERR_FILENO);
					info->data->exit_code = 126;
				}
				else
				{
					ft_putstr3_fd(cmd_matrix[0], ": Permission denied", "\n",
						STDERR_FILENO);
					info->data->exit_code = 126;
				}
			}
		}
		else
		{
			ft_putstr3_fd(cmd_matrix[0], ": command not found", "\n",
				STDERR_FILENO);
			info->data->exit_code = 127;
		}
		free_system(info->data);
		return (NULL);
	}
	return (path);
}

bool is_readable(const char *path)
{
    struct stat statbuf;

 	stat(path, &statbuf);

    if (statbuf.st_mode & S_IRUSR)
		return (true);
	else
		return (false);
}

bool	start_exec(t_info *info)
{
	char	**cmd_matrix;
	char	*path;

	path = NULL;
	cmd_matrix = ms_split(info->data, info->data->cmds[info->curr_cmd], ' ');
	update_path(info->data);
	path = before_exec(info->data->cmds[info->curr_cmd], info, cmd_matrix);
	// printf("path: %s\n", path);
	close_fds(info->data, info);
	if (path == NULL)
	{
		free_2d_null(&cmd_matrix);
		exit(info->data->exit_code);
		// return (true);
	}
	// close_fds(info->data, info);
	if (execve(path, cmd_matrix, info->data->envp) == -1)
	{
		if (cmd_matrix[0][0] == '.' && cmd_matrix[0][1] == '/')
		{
			if (access(cmd_matrix[0], F_OK))
			{
				if (access(cmd_matrix[0], X_OK) == 0)
				{
					ft_putstr3_fd(cmd_matrix[0], ": Permission denied", "\n",
						STDERR_FILENO);
					info->data->exit_code = 126;
				}
				else
				{
					ft_putstr3_fd(cmd_matrix[0], ": No such file or directory", "\n",
						STDERR_FILENO);
					info->data->exit_code = 127;		
				}
			}
			else
			{
				ft_putstr3_fd(cmd_matrix[0], ": Is a directory", "\n",
					STDERR_FILENO);
				info->data->exit_code = 126;
			}
			free_system(info->data);
			exit(info->data->exit_code);
		}
		else
		{
			ft_putstr3_fd(cmd_matrix[0], ": command not found", "\n",
				STDERR_FILENO);
			info->data->exit_code = 127;
			free_system(info->data);
			exit(info->data->exit_code);
		}
	}
	return (true);
}

bool	is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	return (false);
}
