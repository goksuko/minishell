#include "../../includes/minishell.h"


int	create_children(t_data *data)
{
	int		i;
	pid_t	pid;
	pid_t	pid2;
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
		// data->info->limiter = NULL;
		// limiter_check(data);
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
		if (data->info->curr_cmd == data->info->here_doc_cmd)
			pid2 = heredoc_child_process2(data->info);
		i++;
	}
	if (data->info->limiter)
		// pid = finish_heredoc(data);
			unlink("0ur_h3r3_d0c");

	waitpid(pid, &status, 0);
	waitpid(pid2, &status, 0);
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (SUCCESS);
}


pid_t	child_process(t_info *info)
{
	pid_t	pid;
	char **command;

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
		if (info->curr_cmd == info->here_doc_cmd)
			do_heredoc_child(info);
		else if (info->curr_cmd == info->nbr_of_cmds)
		// if (info->curr_cmd == info->nbr_of_cmds)
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
		command = ft_split(info->cmds[info->curr_cmd - 1], ' '); // only for testing purposes
		// printf_array(command); // only for testing purposes
		printf("is_builtin: %d\n", is_builtin(command[0])); // only for testing purposes
		if (is_builtin(command[0])) // only for testing purposes
			info->data->exit_code = execute_builtin(command, info->data); // only for testing purposes
		else
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


pid_t	heredoc_child_process2(t_info *info)
{
	pid_t	pid;
	char **matrix;

	printf("--heredoc_child_process2--\n");
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
		// do_first_child(info);
		// // if (info->fd_out != -10)
		// // 	close_safe(info->fd_out, info);
		// // if (info->fd_in != -10)
		// // 	close_safe(info->fd_in, info);
		// // if (info->pipe_read_end != STDIN_FILENO)
		// // 	close_safe(info->pipe_read_end, info);
		// // if (info->curr_cmd != 1)
		// // 	close_safe(info->pipefd[1], info);

		// printf("---pipe_read_end in loop: %d\n", info->pipe_read_end);
		// printf("ready to start exec\n");
		// start_exec(info);
	}
	else
	{
		do_heredoc_child(info);
		matrix = ft_split("cat", ' ');
		if (execve("/bin/cat", matrix, info->data->envp) == -1)
		{
			close_info(info, matrix);
			printf("test2	\n");
			ft_exit_perror(ERROR_EXECVE, "execve in start_exec");
		}

	}
	return (pid);
}