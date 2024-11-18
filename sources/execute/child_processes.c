/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child_processes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 22:45:47 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/11/18 11:47:29 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	time_to_fork(t_info *info)
{
	pid_t	pid;
	char	**command_array;

	command_array = make_command_array(info->data); // returns NULL if not builtin
	// print_fds(info->data, info);
	pid = ms_fork(info->data);
	if (pid == 0)
	{
		signals_for_kids();
		handle_child_type(info); //does dup2s
		do_child(info->data, info, command_array);
	}
	else
	{
		unset_signals();
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

	}
	// close_fds(info->data, info);
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

	if (assign_fds_and_pipe(data, i) == false)
		return (-250);
	pid = time_to_fork(data->info);
	return (pid);
}

bool	one_builtin(t_data *data)
{
	char	**command_array;

	command_array = make_command_array(data); // returns NULL if not builtin
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
		// close_fds(data, data->info);
		if (pid < 0)
			return (false); //break??
		data->info->curr_cmd++;
		i++;
	}

	// close_fds(data, data->info); // probably not needed
	waitpid(pid, &status, 0);
	while (wait(NULL) > 0) {
		// printf("hi\n");
	}
	// printf("waitpid %d %d\n", waitpid(-1, &status, 0), pid);
	// printf("%d\n", WEXITSTATUS(status));
	if (WIFEXITED(status))
	// {
		data->exit_code = WEXITSTATUS(status);
	// 	return (true);
	// }
	return (true);
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
