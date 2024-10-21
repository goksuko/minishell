/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child_processes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 22:45:47 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/21 11:15:57 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	do_commands(t_data *data, int i)
{
	if (data->info->curr_cmd == data->info->here_doc_cmd)
	{
		if (init_heredoc(data) == false)
			return (false);
		data->info->fds[i][0] = open("0ur_h3r3_d0c", O_RDONLY, 0777);
		if (data->info->fds[i][0] < 0)
			return (false);
	}
	data->info->fd_in = data->info->fds[i][0];
	data->info->fd_out = data->info->fds[i][1];
	if (i != data->nbr_of_cmds - 1)
	{
		if (pipe(data->info->pipefd) == -1)
			return (false);
	}
	data->info->pipe_read_end = data->info->pipefd[0];
	return (true);
}

bool	create_children(t_data *data)
{
	int		i;
	pid_t	pid;
	int		status;

	status = 0;
	handle_signals(CHILD); // TO BE CHECKED IF CORRECT POSITION
	i = 0;
	while (i < data->nbr_of_cmds)
	{
		if (do_commands(data, i) == false)
			return (false);
		pid = child_process(data->info);
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

bool	do_child_of_child(t_info *info)
{
	char	**command;
	bool 	return_value;

	return_value = true;
	command = NULL;
	if (handle_child_type(info) == false)
		return (false);
	command = ft_split(info->data->cmds[info->curr_cmd], ' ');
	if (command == NULL)
		return (false);
	if (is_builtin(command[0]))
	{
		if (handle_builtin(info, command) == false)
			return_value = false;
	}
	else
	{
		if (start_exec(info) == false)
			return_value = false;
	}
	ft_free_matrix(command);
	return (return_value);
}

bool	do_parent_of_child(t_info *info)
{
	if (info->pipe_read_end != STDIN_FILENO
		&& info->curr_cmd == info->data->nbr_of_cmds - 1)
	{
		if (close(info->pipe_read_end) < 0)
			return (false);
	}
	if (info->fd_out != -10)
	{
		if (close(info->fd_out) < 0)
			return (false);
	}
	if (info->fd_in != -10)
	{
		if (close(info->fd_in) < 0)
			return (false);
	}
	if (info->curr_cmd != info->data->nbr_of_cmds - 1)
	{
		if (close(info->pipefd[1]) < 0)
			return (false);
	}
	return (true);
}

pid_t	child_process(t_info *info)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-125);
	else if (pid == 0)
	{
		if (do_child_of_child(info) == false)
			return (-125);
	}
	else
	{
		if (do_parent_of_child(info) == false)
			return (-125);
	}
	return (pid);
}
