/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ms_funcs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/27 12:02:02 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/11/18 11:06:28 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_dup2(t_data *data, int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) < 0)
		ft_exit_perror(data, ERROR_DUP2);
	return ;
}

void	ms_close(t_data *data, int fd)
{
	if (close(fd) < 0)
		ft_exit_perror(data, ERROR_CLOSE);
	return ;
}

int	ms_open(t_data *data, char *file, int flags, int mode)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd < 0)
	{
		free_system(data);
		return (-1);
	}
	return (fd);
}

void	ms_pipe(t_data *data, int *pipefd)
{
	if (pipe(pipefd) < 0)
		ft_exit_perror(data, ERROR_PIPE);
	return ;
}

int	ms_fork(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_exit_perror(data, ERROR_FORK);
	return (pid);
}
