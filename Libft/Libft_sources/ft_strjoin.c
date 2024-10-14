/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 12:29:27 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/14 14:56:56 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*Allocates (with malloc(3)) and returns a new
string, which is the result of the concatenation
of ’s1’ and ’s2’.*/

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	i;
	size_t	j;

	join = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (join == NULL || errno == ENOMEM)
		return (perror("ft_strjoin"), NULL);
	i = 0;
	j = 0;
	while (s1[i] != 0)
	{
		join[j] = s1[i];
		j++;
		i++;
	}
	i = 0;
	while (s2[i] != 0)
	{
		join[j] = s2[i];
		j++;
		i++;
	}
	join[j] = '\0';
	return (join);
}
/*
int	main(void)
{
	char	*s1 = "Hello, ";
	char 	*s2 = "world!";

	printf("%s\n", ft_strjoin(s1, s2));
	return (0);
}
*/