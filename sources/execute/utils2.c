/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/30 23:23:28 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/09/22 23:24:49 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	close_safe(int fd, t_pipex *info)
{
	printf("close_safe %d\n", fd);
	// if (isatty(fd))
	// {
		if (close(fd) < 0)
		{
			close_pipex(info, NULL);
			ft_exit_perror(ERROR_CLOSE, "in close safe");
		}
	// } 
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

char	*ft_strjoin_c(char const *s1, char c)
{
	char	*new_str;
	char	*temp;

	if (s1 == NULL)
		return (NULL);
	new_str = (char *)ft_calloc((ft_strlen(s1)
				+ 1 + 1), sizeof(char));
	if (new_str == NULL)
		return (NULL);
	temp = new_str;
	ft_strlcpy(new_str, s1, ft_strlen(s1) + 1);
	new_str += ft_strlen(s1);
	*new_str = c;
	return (temp);
}