/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child_processes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 22:45:47 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/11/18 12:37:34 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	time_to_fork(t_info *info)
{
	pid_t	pid;
	char	**command_array;

	command_array = make_command_array(info->data);
	pid = ms_fork(info->data);
	if (pid < 0)
		ft_exit_data_perror(info->data, ERROR_FORK, "time_to_fork");
	else if (pid == 0)
	{
		signals_for_kids();
		handle_child_type(info);
		do_child(info->data, info, command_array);
	}
	else
	{
		unset_signals();
		do_parent(info);
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
	data->info->pipe_read_end = data->info->pipefd[0];
	if (i != data->nbr_of_cmds - 1)
		ms_pipe(data, data->info->pipefd);
	return (true);
}

int	pipe_and_fork(t_data *data, int i)
{
	pid_t	pid;

	assign_fds_and_pipe(data, i);
	pid = time_to_fork(data->info);
	return (pid);
}

bool	one_builtin(t_data *data)
{
	char	**command_array;

	command_array = make_command_array(data);
	if (command_array)
	{
		handle_builtin(data->info, command_array);
		close_fds(data, data->info);
		free_2d_null(&command_array);
		return (true);
	}
	return (false);
}

bool	create_children(t_data *data)
{
	int		i;
	pid_t	pid;
	int		status;

	status = 0;
	i = 0;
	if (data->nbr_of_cmds == 1)
	{
		if (one_builtin(data))
			return (true);
	}
	while (i < data->nbr_of_cmds && data->exit_code == 0)
	{
		pid = pipe_and_fork(data, i);
		data->info->curr_cmd++;
		i++;
	}
	waitpid(pid, &status, 0);
	while (wait(NULL) > 0)
	{
	}
	if (WIFEXITED(status))
		data->exit_code = WEXITSTATUS(status);
	return (true);
}
