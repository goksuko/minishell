/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/30 23:23:28 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/26 23:43:23 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	close_safe(int fd, t_info *info)
// {
// 	if (close(fd) < 0)
// 		ft_exit_data_perror(info->data, ERROR_CLOSE, "in close safe");
// 	return (0);
// }

// int	dup2_safe(int oldfd, int newfd, t_info *info)
// {
// 	if (dup2(oldfd, newfd) == -1)
// 		ft_exit_data_perror(info->data, ERROR_DUP2, "in dup2 safe");
// 	return (0);
// }

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
