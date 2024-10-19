#include "../../includes/minishell.h"

bool	do_first_child(t_info *info)
{
	if (info->fd_in != -10)
	{
		if (dup2(info->fd_in, STDIN_FILENO) < 0)
			return (false);
	}
	if (info->fd_out != -10)
	{
		if (dup2(info->fd_out, STDOUT_FILENO) < 0)
			return (false);
	}
	else
	{
		if (dup2(info->pipefd[1], STDOUT_FILENO) < 0)
			return (false);
	}
	return (true);
}

bool	do_middle_child(t_info *info)
{
	if (info->fd_in != -10)
	{
		if (dup2(info->fd_in, STDIN_FILENO) < 0)
			return (false);
	}
	else
	{
		if (dup2(info->pipe_read_end, STDIN_FILENO) < 0)
			return (false);
	}
	if (info->fd_out != -10)
	{
		if (dup2(info->fd_out, STDOUT_FILENO) < 0)
			return (false);
	}
	else
	{
		if (dup2(info->pipefd[1], STDOUT_FILENO) < 0)
			return (false);
	}
	return (true);
}

bool	do_last_child(t_info *info)
{
	if (info->fd_out != -10)
	{
		if (dup2(info->fd_out, STDOUT_FILENO) < 0)
			return (false);
	}
	if (info->fd_in != -10)
	{
		if (dup2(info->fd_in, STDIN_FILENO) < 0)
			return (false);
	}
	else if (info->curr_cmd != 0)
	{
		if (dup2(info->pipe_read_end, STDIN_FILENO) < 0)
			return (false);
	}
	return (true);
}