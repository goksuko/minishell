#include "../../includes/minishell.h"

void do_first_child(t_info *info)
{
	if (info->fd_in != -10)
		dup2_safe(info->fd_in, STDIN_FILENO, info);
	if (info->fd_out != -10)
		dup2_safe(info->fd_out, STDOUT_FILENO, info);
	else
		dup2_safe(info->pipefd[1], STDOUT_FILENO, info);
}

void do_middle_child(t_info *info)
{
	if (info->fd_in != -10)
		dup2_safe(info->fd_in, STDIN_FILENO, info);
	else
		dup2_safe(info->pipe_read_end, STDIN_FILENO, info);
	if (info->fd_out != -10)
		dup2_safe(info->fd_out, STDOUT_FILENO, info);
	else
		dup2_safe(info->pipefd[1], STDOUT_FILENO, info);
}

void do_last_child(t_info *info)
{
	if (info->fd_out != -10)
		dup2_safe(info->fd_out, STDOUT_FILENO, info);
	if (info->fd_in != -10)
		dup2_safe(info->fd_in, STDIN_FILENO, info);
	else if (info->curr_cmd != 0)
		dup2_safe(info->pipe_read_end, STDIN_FILENO, info);
}