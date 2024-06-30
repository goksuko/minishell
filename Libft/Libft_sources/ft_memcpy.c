/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:26:44 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 12:02:11 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*The memcpy() function copies n bytes from memory area src to memory area dest.
The memory areas must not overlap.*/

#include "../includes/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
/*
int	main(void)
{
	char	str[] = "Hello, world!";
	char	dest[50];

	printf("dest org: %s\n", dest);
	ft_memcpy(dest, str, 3);
	printf("my code: %s\n", dest);
	memcpy(dest, str, 3);
	printf("org code: %s\n", dest);
	return (0);
}
*/