/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:26:27 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 12:01:57 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*The  bzero()  function erases the data in the n bytes of the memory starting 
at the location pointed to by s, by writing zeros (bytes containing '\0') 
to that area.*/

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr_str;
	size_t			i;

	i = 0;
	ptr_str = (unsigned char *)s;
	while (i < n)
	{
		ptr_str[i] = '\0';
		i++;
	}
}
/*
int	main(void)
{
	char	str[50] = "Hello, world!";

	printf(" str org: %s\n", str);
	ft_bzero(str, 3);
	printf(" my code: %s\n", str);
	strcpy(str, "Hello, world!");
	printf(" str org: %s\n", str);
	bzero(str, 3);
	printf("org code: %s\n", str);
	return (0);
}
*/