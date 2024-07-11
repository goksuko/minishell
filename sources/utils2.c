/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/30 23:23:28 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/07/11 12:28:12 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	close_safe(int fd, t_pipex *info)
{
	printf("close_safe %d\n", fd);
	if (close(fd) < 0)
	{
		close_pipex(info, NULL);
		ft_exit_perror(ERROR_CLOSE, "in close safe");
	}
	return (0);
}

int	dup2_safe(int oldfd, int newfd, t_pipex *info)
{
	printf("dup2_safe %d, %d \n", oldfd, newfd);
	if (dup2(oldfd, newfd) == -1)
	{
		close_pipex(info, NULL);
		ft_exit_perror(ERROR_DUP2, "in dup2 safe");
	}
	// close_safe(oldfd, info);
	return (0);
}
