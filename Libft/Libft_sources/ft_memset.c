/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:26:13 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 12:02:11 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*The memset() function fills the first n bytes of the memory area pointed 
to by s with the constant byte c. 
The memset() function returns a pointer to the memory area s.*/

#include "../includes/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (p);
}
/*
int	main(void)
{
	char	str[50] = "Hello, world!";

	printf(" str org: %s\n", str);
	ft_memset(str, 'A', 5);
	printf(" my code: %s\n", str);
	memset(str, 'A', 5);
	printf("org code: %s\n", str);
	return (0);
}
*/