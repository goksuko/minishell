/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/30 23:23:28 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/13 22:19:25 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	close_safe(int fd, t_info *info)
{
	printf("close_safe %d\n", fd);
	// if (isatty(fd))
	// {
		if (close(fd) < 0)
		{
			close_info(info);
			printf("error in close_safe %d:\n", fd);
			ft_exit_perror(ERROR_CLOSE, "in close safe");
		}
	// } 
	return (0);
}

int	dup2_safe(int oldfd, int newfd, t_info *info)
{
	printf("dup2_safe %d, %d \n", oldfd, newfd);
	if (dup2(oldfd, newfd) == -1)
	{
		close_info(info);
		printf("error in dup2_safe %d, %d:\n", oldfd, newfd);
		ft_exit_perror(ERROR_DUP2, "in dup2 safe");
	}
	// close_safe(oldfd, info);
	return (0);
}

char	*ft_strcpy(char *dest, char *src, int len)
{
	int	i;

	i = 0;
	while (src[i] != '\0' && len != 0)
	{
		dest[i] = src[i];
		i++;
		len--;
	}
	dest[i] = '\0';
	return (dest);
}
