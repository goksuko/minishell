/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   children.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 22:59:07 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/23 23:54:24 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	do_first_child(t_info *info)
{
	if (info->fd_in != -10)
	{
		if (dup2(info->fd_in, STDIN_FILENO) < 0)
			return (error_assign(info->data, ERROR_DUP2));
	}
	if (info->fd_out != -10)
	{
		if (dup2(info->fd_out, STDOUT_FILENO) < 0)
			return (error_assign(info->data, ERROR_DUP2));
	}
	else
	{
		if (dup2(info->pipefd[1], STDOUT_FILENO) < 0)
			return (error_assign(info->data, ERROR_DUP2));
	}
	return (SUCCESS);
}

int	do_middle_child(t_info *info)
{
	if (info->fd_in != -10)
	{
		if (dup2(info->fd_in, STDIN_FILENO) < 0)
			return (error_assign(info->data, ERROR_DUP2));
	}
	else
	{
		if (dup2(info->pipe_read_end, STDIN_FILENO) < 0)
			return (error_assign(info->data, ERROR_DUP2));
	}
	if (info->fd_out != -10)
	{
		if (dup2(info->fd_out, STDOUT_FILENO) < 0)
			return (error_assign(info->data, ERROR_DUP2));
	}
	else
	{
		if (dup2(info->pipefd[1], STDOUT_FILENO) < 0)
			return (error_assign(info->data, ERROR_DUP2));
	}
	return (SUCCESS);
}

int	do_last_child(t_info *info)
{
	if (info->fd_out != -10)
	{
		if (dup2(info->fd_out, STDOUT_FILENO) < 0)
			return (error_assign(info->data, ERROR_DUP2));
	}
	if (info->fd_in != -10)
	{
		if (dup2(info->fd_in, STDIN_FILENO) < 0)
			return (error_assign(info->data, ERROR_DUP2));
	}
	else if (info->curr_cmd != 0)
	{
		if (dup2(info->pipe_read_end, STDIN_FILENO) < 0)
			return (error_assign(info->data, ERROR_DUP2));
	}
	return (SUCCESS);
}

int	handle_child_type(t_info *info)
{
	if (info->curr_cmd == info->data->nbr_of_cmds - 1)
	{
		if (do_last_child(info) > 0)
			return (info->data->exit_code);
	}
	else if (info->curr_cmd == 0)
	{
		if (do_first_child(info) > 0)
			return (info->data->exit_code);
	}
	else
	{
		if (do_middle_child(info) > 0)
			return (info->data->exit_code);
	}
	return (SUCCESS);
}

int	handle_builtin(t_data *data, char **command)
{
	// printf("handle_builtin\n");
	// printf("fd_in: %d, fd_out: %d\n", data->info->fd_in, data->info->fd_out);
	printf("fd_in: %d, fd_out: %d\n", data->info->fds[0][0],
		data->info->fds[0][1]);
	if (data->info->fds[0][0] != -10)
		data->info->fd_in = data->info->fds[0][0];
	if (data->info->fds[0][1] != -10)
		data->info->fd_out = data->info->fds[0][1];
	if (command && command[0])
		data->exit_code = execute_builtin(command, data);
	// printf("exit code in handle_builtin: %d\n", data->exit_code);
	if (data->info->fds[0][0] != -10)
	{
		if (close(data->info->fd_in) < 0)
			return (error_assign(data, ERROR_CLOSE));
	}
	if (data->info->fds[0][1] != -10)
	{
		if (close(data->info->fd_out) < 0)
			return (error_assign(data, ERROR_CLOSE));
	}
	return (data->exit_code);
}
