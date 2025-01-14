/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   children.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 22:59:07 by akaya-oz      #+#    #+#                 */
/*   Updated: 2025/01/14 23:15:48 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	do_first_child(t_info *info)
{
	if (info->fd_in != -10)
	{
		ms_dup2(info->data, info->fd_in, STDIN_FILENO);
		ms_close(info->data, info->fd_in);
	}
	// {
	// 	if (dup2(info->fd_in, STDIN_FILENO) < 0)
	// 		return (false);
	// }
	if (info->fd_out != -10)
		ms_dup2(info->data, info->fd_out, STDOUT_FILENO);
	// {
	// 	if (dup2(info->fd_out, STDOUT_FILENO) < 0)
	// 		return (false);
	// }
	else
		ms_dup2(info->data, info->pipefd[1], STDOUT_FILENO);
	// {
	// 	if (dup2(info->pipefd[1], STDOUT_FILENO) < 0)
	// 		return (false);
	// }
	return (true);
}

bool	do_middle_child(t_info *info)
{
	if (info->fd_in != -10)
	{
		ms_dup2(info->data, info->fd_in, STDIN_FILENO);
		ms_close(info->data, info->fd_in);
	}
	// {
	// 	if (dup2(info->fd_in, STDIN_FILENO) < 0)
	// 		return (false);
	// }
	else
	{
		ms_dup2(info->data, info->pipe_read_end, STDIN_FILENO);
		ms_close(info->data, info->pipe_read_end);
	}
	// {
	// 	if (dup2(info->pipe_read_end, STDIN_FILENO) < 0)
	// 		return (false);
	// }
	if (info->fd_out != -10)
		ms_dup2(info->data, info->fd_out, STDOUT_FILENO);
	// {
	// 	if (dup2(info->fd_out, STDOUT_FILENO) < 0)
	// 		return (false);
	// }
	else
		ms_dup2(info->data, info->pipefd[1], STDOUT_FILENO);
	// {
	// 	if (dup2(info->pipefd[1], STDOUT_FILENO) < 0)
	// 		return (false);
	// }
	return (true);
}

bool	do_last_child(t_info *info)
{
	if (info->fd_out != -10)
		ms_dup2(info->data, info->fd_out, STDOUT_FILENO);
	// {
	// 	if (dup2(info->fd_out, STDOUT_FILENO) < 0)
	// 		return (false);
	// }
	if (info->fd_in != -10)
	{
		ms_dup2(info->data, info->fd_in, STDIN_FILENO);
		ms_close(info->data, info->fd_in);
	}
	// {
	// 	if (dup2(info->fd_in, STDIN_FILENO) < 0)
	// 		return (false);
	// }
	else if (info->curr_cmd != 0)
	{
		ms_dup2(info->data, info->pipe_read_end, STDIN_FILENO);
		ms_close(info->data, info->pipe_read_end);
	}
	// {
	// 	if (dup2(info->pipe_read_end, STDIN_FILENO) < 0)
	// 		return (false);
	// }
	return (true);
}

bool	handle_child_type(t_info *info)
{
	if (info->curr_cmd == info->data->nbr_of_cmds - 1)
	{
		if (do_last_child(info) == false)
			return (false);
	}
	else if (info->curr_cmd == 0)
	{
		if (do_first_child(info) == false)
			return (false);
	}
	else
	{
		if (do_middle_child(info) == false)
			return (false);
	}
	return (true);
}

bool	handle_builtin(t_info *info, char **command)
{
	if (command && command[0])
		info->data->exit_code = execute_builtin(command, info->data);
	if (info->data->exit_code != 0)
		return (false);
	return (true);
}
