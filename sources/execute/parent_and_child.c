/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parent_and_child.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/27 01:13:14 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/11/18 12:19:26 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	close_fds(t_data *data, t_info *info)
{
	if (info->pipefd[0] != STDIN_FILENO)
	{
		ms_close(data, info->pipefd[0]);
		info->pipefd[0] = STDIN_FILENO;
	}
	if (info->fd_out != -10)
	{
		ms_close(data, info->fd_out);
		info->fd_out = -10;
	}
	if (info->fd_in != -10)
	{
		ms_close(data, info->fd_in);
		info->fd_in = -10;
	}
	if (info->pipefd[1] != STDOUT_FILENO)
	{
		ms_close(data, info->pipefd[1]);
		info->pipefd[1] = STDOUT_FILENO;
	}
	return (true);
}

bool	print_fds(t_data *data, t_info *info)
{
	(void)data;
	if (info->pipefd[0] != STDIN_FILENO)
	{
		printf("pipefd[0]: %d\n", info->pipefd[0]);
	}
	if (info->fd_out != -10)
	{
		printf("fd_out: %d\n", info->fd_out);
	}
	if (info->fd_in != -10)
	{
		printf("fd_in: %d\n", info->fd_in);
	}
	if (info->pipefd[1] != STDOUT_FILENO)
	{
		printf("pipefd[1]: %d\n", info->pipefd[1]);
	}
	if (info->pipe_read_end != STDIN_FILENO)
	{
		printf("pipe_read_end: %d\n", info->pipe_read_end);
	}
	return (true);
}

bool	do_child(t_data *data, t_info *info, char **command_array)
{
	if (command_array)
	{
		if (handle_builtin(info, command_array) == false)
		{
			close_fds(data, info);
			close_fds_from_next_cmds(info);
			exit(EXIT_FAILURE);
		}
		else
		{
			close_fds(data, info);
			close_fds_from_next_cmds(info);
			exit(EXIT_SUCCESS);
		}
	}
	else
	{
		if (start_exec(info) == false)
			return (false);
	}
	return (true);
}

void	do_parent(t_info *info)
{
	if (info->fd_out != -10)
	{
		ms_close(info->data, info->fd_out);
		info->fd_out = -10;
	}
	if (info->fd_in != -10)
	{
		ms_close(info->data, info->fd_in);
		info->fd_in = -10;
	}
	if (info->pipefd[1] != STDOUT_FILENO)
	{
		ms_close(info->data, info->pipefd[1]);
		info->pipefd[1] = STDOUT_FILENO;
	}
	if (info->pipe_read_end != STDIN_FILENO)
	{
		ms_close(info->data, info->pipe_read_end);
		if (info->pipefd[0] != STDIN_FILENO)
			info->pipe_read_end = info->pipefd[0];
		else
			info->pipe_read_end = STDIN_FILENO;
	}
	return ;
}

char	**make_command_array(t_data *data)
{
	char	**command_array;

	if (data->cmds[data->info->curr_cmd] == NULL)
		return (NULL);
	command_array = ms_split(data, data->cmds[data->info->curr_cmd], ' ');
	if (is_builtin(command_array[0]))
		return (command_array);
	free_2d_null(&command_array);
	return (NULL);
}
