#include "../../includes/minishell.h"


int	create_children(t_data *data)
{
	int		i;
	pid_t	pid;
	// pid_t	pid_last;
	int		status;

	printf("---create_children---\n");
	i = 0;
	data->info->pipe_read_end = STDIN_FILENO;
	// printf("nbr_of_cmds: %d\n**********\n", data->nbr_of_cmds);
	while (i < data->info->nbr_of_cmds)
	{
		printf("\nin while loop i: %d\n", i);
		// define_fd_in_out(data->info);
		data->info->fd_in = data->info->fds[i][0];
		data->info->fd_out = data->info->fds[i][1];
		data->info->limiter = NULL;
		limiter_check(data);
		// if (data->tokens->value == data->info->limiter)
		// 	break ;
		printf("limiter after limiter_check: %s\n", data->info->limiter);
		printf("info->fds[0][0]: %d\n", data->info->fds[0][0]);
		printf("info->fds[0][1]: %d\n", data->info->fds[0][1]);
		printf("fd_out just after define_fd: %d\n", data->info->fd_out);
		if (i != data->nbr_of_cmds - 1)
		{
			if (pipe(data->info->pipefd) == -1)
				ft_close_exit_perror(data->info, NULL, ERROR_PIPE, "pipe in create children");
		}
		printf("fd_out just before child process: %d\n", data->info->fd_out);
		printf("cmds: \n");	
		printf_array(data->info->cmds);
		pid = child_process(data->info);
		data->info->pipe_read_end = data->info->pipefd[0];
		data->info->curr_cmd++;
		printf("sleeping after child (%d)\n", i);
		sleep(1);
		i++;
	}
	if (data->info->limiter)
		// pid = finish_heredoc(data);
			unlink("0ur_h3r3_d0c");

	waitpid(pid, &status, 0);
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (SUCCESS);
}


pid_t	child_process(t_info *info)
{
	pid_t	pid;

	printf("--child_process--\n");
	pid = fork();
	if (pid == -1)
	{
		close_info(info, NULL);
		ft_exit_perror(ERROR_FORK, "fork in child process");
	}
	else if (pid == 0)
	{
		printf("curr_cmd: %d\n", info->curr_cmd);
		printf("pipefd[0]: %d\n", info->pipefd[0]);
		printf("pipefd[1]: %d\n", info->pipefd[1]);

		if (info->curr_cmd == info->nbr_of_cmds)
			do_last_child(info);
		else if (info->curr_cmd == 1)
			do_first_child(info);
		else
			do_middle_child(info);
		// if (info->fd_out != -10)
		// 	close_safe(info->fd_out, info);
		// if (info->fd_in != -10)
		// 	close_safe(info->fd_in, info);
		// if (info->pipe_read_end != STDIN_FILENO)
		// 	close_safe(info->pipe_read_end, info);
		// if (info->curr_cmd != 1)
		// 	close_safe(info->pipefd[1], info);

		printf("---pipe_read_end in loop: %d\n", info->pipe_read_end);
		printf("ready to start exec\n");
		start_exec(info);
	}
	else
	{
		if (info->pipe_read_end != STDIN_FILENO)
			close_safe(info->pipe_read_end, info);
		if (info->fd_out != -10)
			close_safe(info->fd_out, info);
		if (info->fd_in != -10)
			close_safe(info->fd_in, info);
		if (info->curr_cmd != 1)
			close_safe(info->pipefd[1], info);
	}
	return (pid);
}
