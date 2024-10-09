#include "../../includes/minishell.h"

void do_first_child(t_pipex *info)
{
	printf("do_first_child\n");
	if (info->fd_in != -10)
	{
		dup2_safe(info->fd_in, STDIN_FILENO, info); // it was fd_in before actually
		// close_safe(info->fd_in, info);
		// close_safe(info->pipefd[0], info);
	}
	if (info->fd_out != -10)
	{
		dup2_safe(info->fd_out, STDOUT_FILENO, info);
		// close_safe(info->fd_out, info);
	}
	else
	{
		dup2_safe(info->pipefd[1], STDOUT_FILENO, info);
	}
	// close_safe(info->pipefd[1], info);
	// info->pipe_read_end = info->pipefd[1];
}

void do_middle_child(t_pipex *info)
{
	printf("do_middle_child\n");
	if (info->fd_in != -10)
	{
		dup2_safe(info->fd_in, STDIN_FILENO, info); // it was fd_in before actually
		// close_safe(info->fd_in, info);
	}
	else
	{
		printf("pipe_read_end in middle child: %d\n", info->pipe_read_end);
		dup2_safe(info->pipe_read_end, STDIN_FILENO, info);
		// close_safe(info->pipe_read_end, info);
	}
	if (info->fd_out != -10)
	{
		dup2_safe(info->fd_out, STDOUT_FILENO, info);
		// close_safe(info->fd_out, info);
	}
	else
	{
		dup2_safe(info->pipefd[1], STDOUT_FILENO, info);
	}
	// close_safe(info->pipefd[1], info);
	// info->pipe_read_end = info->pipefd[1];
}

void do_last_child(t_pipex *info)
{
	printf("do_last_child\n");
	printf("pipe_read_end in last child: %d\n", info->pipe_read_end);	
	printf("pipefd[0]: %d\n", info->pipefd[0]);	
	printf("pipefd[1]: %d\n", info->pipefd[1]);
	printf("fd_in: %d\n", info->fd_in);
	printf("fd_out: %d\n", info->fd_out);
	if (info->fd_out != -10)
	{
		dup2_safe(info->fd_out, STDOUT_FILENO, info);
		// close_safe(info->fd_out, info);
	}
	// if (info->fd_in != -10)
	if (info->fd_in != -10 && info->curr_cmd == 1) //changed but not sure
	{
		dup2_safe(info->fd_in, STDIN_FILENO, info);
		// close_safe(info->fd_in, info); //ben kapattim
	}
	else if (info->curr_cmd != 1)
	{
		printf("pipe_read_end in last child: %d\n", info->pipe_read_end);
		dup2_safe(info->pipe_read_end, STDIN_FILENO, info);
		// close_safe(info->pipe_read_end, info);
	}

	// close_safe(info->pipefd[1], info);
}