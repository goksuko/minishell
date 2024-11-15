/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child_processes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 22:45:47 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/11/15 13:00:28 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	time_to_fork(t_info *info)
{
	pid_t	pid;
	char	**command_array;

	command_array = make_command_array(info->data); // returns NULL if not builtin
	// printf("----COMMAND ARRAY----\n"); // DEBUGGING PURPOSES!
	// printf_array(command_array); // DEBUGGING PURPOSES!
	printf("to for for cmd: %d\n", info->curr_cmd);
	print_fds(info->data, info);
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
		// if (do_parent(info->data, info, command_array) == false)
		// 	pid = -125;
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

// bool	create_children(t_data *data)
// {
// 	int		i;
// 	pid_t	pid;
// 	int		status;
// 	char	**command_array;
// 	int		kid_pids[100];
// 	int		j;
// 	bool	is_builtin;
// 	bool	forked;

// 	status = 0;
// 	i = 0;
// 	j = 0;
// 	is_builtin = false;
// 	printf("---cmds:\n"); // DEBUGGING PURPOSES!
// 	printf_array(data->cmds); // DEBUGGING PURPOSES!
// 	printf("--------\n"); // DEBUGGING PURPOSES!
// 	if (data->nbr_of_cmds == 1)
// 	{
// 		command_array = make_command_array(data); // returns NULL if not builtin
// 		if (command_array)
// 		{
// 			handle_builtin(data->info, command_array);
// 			close_fds(data, data->info);
// 			return (true);
// 		}
// 	}
// 	while (i < data->nbr_of_cmds && data->exit_code == 0)
// 	{
// 		forked = false;
// 		command_array = make_command_array(data); // returns NULL if not builtin
// 		if (command_array)
// 			is_builtin = true;
// 		if (data->info->curr_cmd == data->info->here_doc_cmd)
// 		{
// 			if (init_heredoc(data) == false)
// 				return (false);
// 			data->info->fds[i][0] = ms_open(data, "0ur_h3r3_d0c", O_RDONLY, 0777);
// 		}
// 		data->info->fd_in = data->info->fds[i][0];
// 		data->info->fd_out = data->info->fds[i][1];
// 		if (i != data->nbr_of_cmds - 1)
// 			ms_pipe(data, data->info->pipefd);
// 		// else
// 		// {
// 		// 	data->info->pipefd[0] = STDIN_FILENO;			
// 		// 	data->info->pipefd[1] = STDOUT_FILENO;
// 		// }
// 		data->info->pipe_read_end = data->info->pipefd[0];
// 		// printf("----COMMAND ARRAY----\n"); // DEBUGGING PURPOSES!
// 		// printf_array(command_array); // DEBUGGING PURPOSES!
// 		if (data->nbr_of_cmds > 1 || !is_builtin)
// 		{
// 			pid = ms_fork(data);
// 			// printf("----FORKED----\n"); // DEBUGGING PURPOSES!
// 			forked = true;
// 		}
// 		// else
// 		// 	pid = 1;
// 		// if (pid == 0 || pid == 1)
// 		if (pid == 0 || is_builtin)
// 		{
// 			signals_for_kids();
// 			if (!is_builtin)
// 				handle_child_type(data->info); //does dup2s
// 			if (is_builtin)
// 			{
// 				if (handle_builtin(data->info, command_array) == false)
// 				{
// 					printf("--HANDLE BUILTIN RETURNED FALSE\n"); // DEBUG
// 					close_fds(data, data->info);
// 					close_fds_from_next_cmds(data->info);
// 					if (forked)
// 						exit(EXIT_FAILURE);
// 					else
// 						unset_signals();
// 				}
// 				else
// 				{
// 					printf("---HANLDE BUILTIN RETURNED TRUE---\n"); // DEBUG
// 					close_fds(data, data->info);
// 					printf("---Close FDs done in do_child\n");
// 					close_fds_from_next_cmds(data->info);
// 					if (forked)
// 						exit(EXIT_SUCCESS);
// 					else
// 						unset_signals();
// 				}
// 			}
// 			else
// 			{
// 				// data->exit_code = SUCCESS;
// 				if (start_exec(data->info) == false)
// 					return (false);
// 			}
// 		}
// 		else
// 		{
// 			unset_signals();
// 			// if (do_parent(data, data->info, command_array) == false)
// 			// 	pid = -125;
// 		}
// 		close_fds(data, data->info);
// 		free_2d_null(&command_array);
// 		if (pid < 0)
// 			return (false); //break??
// 		data->info->curr_cmd++;
// 		kid_pids[i] = pid;
// 		i++;
// 	}
// 	waitpid(pid, &status, 0);
// 	while (j < i)
// 	{
// 		if (kid_pids[j] != 1)
// 			waitpid(kid_pids[j], &status, 0);
// 		j++;
// 	}
// 	// close_fds(data, data->info); // probably not needed
// 	// waitpid(-1, &status, 0);
// 	// if (WIFEXITED(status))
// 	// {
// 	// 	data->exit_code = WEXITSTATUS(status);
// 	// 	return (true);
// 	// }
// 	return (true);
// }

bool	one_builtin(t_data *data)
{
	char	**command_array;

	command_array = make_command_array(data); // returns NULL if not builtin
	if (command_array)
	{
		handle_builtin(data->info, command_array);
		close_fds(data, data->info);
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
	printf("---cmds:\n"); // DEBUGGING PURPOSES!
	printf_array(data->cmds); // DEBUGGING PURPOSES!
	printf("--------\n"); // DEBUGGING PURPOSES!
	if (data->nbr_of_cmds == 1)
	{
		if (one_builtin(data))
			return (true);
	}
	while (i < data->nbr_of_cmds && data->exit_code == 0)
	{
		pid = pipe_and_fork(data, i);
		printf("%d\n", pid);
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
	// if (WIFEXITED(status))
	// {
	// 	data->exit_code = WEXITSTATUS(status);
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
