/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ms_funcs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/27 12:02:02 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/11/08 15:32:00 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_dup2(t_data *data, int old_fd, int new_fd)
{
	printf("dup2 %d, %d\n", old_fd, new_fd);
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
		ft_printf_fd(STDERR_FILENO, "bash: %s: Permission denied\n",
			"token->next->value");
		data->exit_code = ERROR_NO_FILE_DIR;
		free_system(data);
		return (-1);
	}
	ft_printf("ms_open %d: %s\n", fd, file);
	return (fd);
}

void	ms_pipe(t_data *data, int *pipefd)
{
	if (pipe(pipefd) < 0)
		ft_exit_perror(data, ERROR_PIPE);
	printf("pipe %d %d\n", pipefd[0], pipefd[1]);
	return ;
}

int	ms_fork(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_exit_perror(data, ERROR_FORK);
	printf("fork %d\n", pid);
	return (pid);
}
