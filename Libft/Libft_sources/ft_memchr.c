/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:29:10 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 12:02:10 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*The  memchr()  function  scans  the initial n bytes of the memory area pointed
to by s for the first instance of c. Both c and the bytes of the memory area 
pointed to by s are interpreted as unsigned char.The memchr() and memrchr() 
functions return a pointer to the matching byte or NULL if the character 
does not occur in the given memory area.*/

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	ch;

	p = (unsigned char *)s;
	ch = (unsigned char)c;
	while (n--)
	{
		if (*p == ch)
			return (p);
		p++;
	}
	return (NULL);
}
/*
int	main(void)
{
	const void	*s;

	s = "Hello, world!";
	char s2[] = {0, 1, 2, 3, 4, 5};
	int c = 258; //unsigned char overflow -> 2

	printf("org code: %p\n", memchr(s, 'l', 2));
	printf(" my code: %p\n", ft_memchr(s, 'l', 2));
	printf("org code: %p\n", memchr(s, 'l', 5));
	printf(" my code: %p\n", ft_memchr(s, 'l', 5));
	printf("org code: %p\n", memchr(s2, c, 3));
	printf(" my code: %p\n", ft_memchr(s2, c, 3));
	return (0);
}
*/