/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   child_processes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 22:45:47 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/23 23:56:30 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	assign_fds_and_pipe(t_data *data, int i)
{
	data->info->fd_in = data->info->fds[i][0];
	data->info->fd_out = data->info->fds[i][1];
	if (i != data->nbr_of_cmds - 1)
	{
		if (pipe(data->info->pipefd) == -1)
			return (error_assign(data, ERROR_PIPE));
	}
	data->info->pipe_read_end = data->info->pipefd[0];
	printf("pipefd[0] = %d\n", data->info->pipefd[0]);
	printf("pipefd[1] = %d\n", data->info->pipefd[1]);
	return (SUCCESS);
}

int	create_children(t_data *data)
{
	int		i;
	pid_t	pid;
	int		status;

	status = 0;
	i = 0;
	while (i < data->nbr_of_cmds)
	{
		// TO CHECK maybe it is necessary to fork to use the signal inside the heredoc
		if (assign_fds_and_pipe(data, i) > 0)
			return (data->exit_code);
		pid = child_process(data->info);
		if (pid < 0)
			return (data->exit_code);
		// ???? signals
		data->info->curr_cmd++;
		i++;
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		// printf("exit code after fork 1: %d\n", data->exit_code);
		if (data->exit_code > 0)
			break ;
	}
	waitpid(pid, &status, 0);
	// do_parent_of_child(data->info); // to close open files
	waitpid(-1, &status, 0);
	return (data->exit_code);
}

// we need to exit the cild process
// everything that has been created in the parent will need to
int	do_child_of_child(t_info *info)
{
	// TO CHECK include an exit of the child process
	// char	**command;
	// command = NULL;
	if (handle_child_type(info) > 0)
		return (info->data->exit_code);
	// command = ft_split(info->data->cmds[info->curr_cmd], ' ');
	// if (command == NULL)
	// 	return(error_assign(info->data, ERROR_ALLOCATION));
	// if (is_builtin(command[0]))
	// {
	// 	if (handle_builtin(info->data, command) > 0)
	// 	{
	// 		ft_free_matrix(command);
	// 		return(info->data->exit_code);
	// 	}
	// }
	// else
	// {
	// 	ft_free_matrix(command);
	if (start_exec(info) > 0)
	{
		// ft_free_matrix(command);
		return (info->data->exit_code);
	}
	// }
	// ft_free_matrix(command);
	return (SUCCESS);
}

int	do_parent_of_child(t_info *info)
{
	if (info->pipe_read_end != STDIN_FILENO
		&& info->curr_cmd == info->data->nbr_of_cmds - 1)
	{
		printf("to be closed: %d\n", info->pipe_read_end);
		if (close(info->pipe_read_end) < 0)
			return (error_assign(info->data, ERROR_CLOSE));
	}
	if (info->fd_out != -10)
	{
		printf("to be closed: %d\n", info->fd_out);
		if (close(info->fd_out) < 0)
			return (error_assign(info->data, ERROR_CLOSE));
	}
	if (info->fd_in != -10)
	{
		printf("to be closed: %d\n", info->fd_in);
		if (close(info->fd_in) < 0)
			return (error_assign(info->data, ERROR_CLOSE));
	}
	if (info->curr_cmd != info->data->nbr_of_cmds - 1)
	{
		printf("to be closed: %d\n", info->pipefd[1]);
		if (close(info->pipefd[1]) < 0)
			return (error_assign(info->data, ERROR_CLOSE));
	}
	// if (info->pipefd[0] != STDOUT_FILENO && info->curr_cmd == 0)
	// {
	// 	printf("to be closed: %d\n", info->pipefd[0]);
	// 	if (close(info->pipefd[0]) < 0)
	// 		return (error_assign(info->data, ERROR_CLOSE));
	// }
	return (SUCCESS);
}

pid_t	child_process(t_info *info)
{
	pid_t	pid;
	int		exit_code;
	int		status;

	pid = fork();
	handle_signals(CHILD); // TO BE CHECKED IF CORRECT POSITION
	if (pid == -1)
		return (error_assign(info->data, ERROR_FORK), -1);
	else if (pid == 0)
	{
		exit_code = do_child_of_child(info);
		info->data->exit_code = exit_code;
		do_parent_of_child(info); // to close open files
									// printf("exit code after do_child_of_child before exit:
									//						%d\n",
		// info->data->exit_code);
		exit(exit_code);
		// if (do_child_of_child(info) == false)
		// 	return (-125);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		info->data->exit_code = WEXITSTATUS(status);
		// printf("exit code in parent after waitpid 3: %d\n",
		//	info->data->exit_code);
		// } else {
		//     info->data->exit_code = -1;
		// Indicate an error if the child did not exit normally
	}
	waitpid(-1, &status, 0);
	do_parent_of_child(info);
	// if (do_parent_of_child(info) > 0)
	// return (-125);
	// if (info->data->exit_code > 0)
	// 	return (-125);
	return (pid);
}
