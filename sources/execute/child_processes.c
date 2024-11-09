/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child_processes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 22:45:47 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/11/09 22:18:27 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	time_to_fork(t_info *info)
{
	pid_t	pid;
	char	**command_array;

	command_array = make_command_array(info->data);
	pid = ms_fork(info->data);
	if (pid == 0)
	{
		signals_for_kids();
		handle_child_type(info);
		do_child(info->data, info, command_array);
		close_fds(info->data, info);
	}
	else
	{
		unset_signals();
		if (do_parent(info->data, info, command_array) == false)
			return (-125);
		close_fds(info->data, info);
	}
	free_2d_null(&command_array);
	return (pid);
}

bool	assign_fds_and_pipe(t_data *data, int i)
{
	if (data->info->curr_cmd == data->info->here_doc_cmd)
	{
		if (init_heredoc(data) == false)
			return (false);
		data->info->fds[i][0] = ms_open(data, "0ur_h3r3_d0c", O_RDONLY, 0777);
	}
	data->info->fd_in = data->info->fds[i][0];
	data->info->fd_out = data->info->fds[i][1];
	if (i != data->nbr_of_cmds - 1)
		ms_pipe(data, data->info->pipefd);
	data->info->pipe_read_end = data->info->pipefd[0];
	return (true);
}

int	pipe_and_fork(t_data *data, int i)
{
	pid_t	pid;

	if (assign_fds_and_pipe(data, i) == false)
		return (-250);
	pid = time_to_fork(data->info);
	if (pid == -125)
		return (-125);
	return (pid);
}

bool	create_children(t_data *data)
{
	int		i;
	pid_t	pid;
	int		status;

	status = 0;
	i = 0;
	// printf("cmds\n"); // DEBUGGING PURPOSES!
	// printf_array(data->cmds); // DEBUGGING PURPOSES!
	while (i < data->nbr_of_cmds)
	{
		// TO CHECK maybe it is necessary to fork to use the signal inside the heredoc
		// if (assign_fds_and_pipe(data, i) == false)
		// 	return (false);
		// pid = time_to_fork(data->info);
		// if (pid == -125)
		// 	return (false);
		pid = pipe_and_fork(data, i);
		if (pid < 0)
			return (false);
		close_fds(data, data->info);
		data->info->curr_cmd++;
		i++;
	}
	waitpid(pid, &status, 0);
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
	{
		data->exit_code = WEXITSTATUS(status);
		return (true);
	}
	return (true);
}

char	**make_command_array(t_data *data)
{
	char	**command_array;

	command_array = ms_split(data, data->cmds[0], ' ');
	if (is_builtin(command_array[0]))
		return (command_array);
	free_2d_null(&command_array);
	return (NULL);
}
