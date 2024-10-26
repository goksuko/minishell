/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child_processes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 22:45:47 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/26 23:14:46 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

bool	create_children(t_data *data)
{
	int		i;
	pid_t	pid;
	int		status;

	status = 0;
	i = 0;
	printf("number of commands for which to create child processes: %d\n", data->nbr_of_cmds);
	while (i < data->nbr_of_cmds)
	{
		//TO CHECK maybe it is necessary to fork to use the signal inside the heredoc
		if (assign_fds_and_pipe(data, i) == false)
			return (false);
		pid = time_to_fork(data->info);
		if (pid == -125)
			return (false);
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

bool	do_child_of_child(t_data *data, t_info *info, char **command_array)
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

bool	do_parent_of_child(t_data *data, t_info *info, char **command_array)
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

char	**make_command_array(t_data *data)
{
	char	**command_array;

	command_array = ms_split(data, data->cmds[0], ' ');
	if (is_builtin(command_array[0]))
		return (command_array);
	return (NULL);
}

pid_t	time_to_fork(t_info *info)
{
	pid_t	pid;
	char	**command_array;

	command_array = make_command_array(info->data);
	pid = ms_fork(info->data);
	if (pid == 0)
	{
		signals_for_kids();
		do_child_of_child(info->data, info, command_array);
	}
	else
	{
		unset_signals();
		if (do_parent_of_child(info->data, info, command_array) == false)
			return (-125);
	}
	return (pid);
}
