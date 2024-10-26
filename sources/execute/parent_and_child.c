/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parent_and_child.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/27 01:13:14 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/27 01:16:45 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	do_child(t_data *data, t_info *info, char **command_array)
{
	(void)data;
	if (command_array)
	{
		if (handle_builtin(info, command_array) == false)
			exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
	}
	else
	{
		if (start_exec(info) == false)
			return (false);
	}
	return (true);
}

bool	do_parent(t_data *data, t_info *info, char **command_array)
{
	(void)data;
	(void)command_array;
	// if (command_array)
	// {
	// 	if (handle_parent_builtin(info, command_array) == false)
	// 		return (false);
	// }
	if (info->pipe_read_end != STDIN_FILENO
		&& info->curr_cmd == info->data->nbr_of_cmds - 1)
		ms_close(data, info->pipe_read_end);
	if (info->fd_out != -10)
		ms_close(data, info->fd_out);
	if (info->fd_in != -10)
		ms_close(data, info->fd_in);
	if (info->curr_cmd != info->data->nbr_of_cmds - 1)
		ms_close(data, info->pipefd[1]);
	return (true);
}
