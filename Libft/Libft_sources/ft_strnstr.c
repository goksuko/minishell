/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:29:34 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 12:02:16 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*The strnstr() function locates the first	occurrence of 
the  null-terminated  string little in the string big, 
where not more than len characters are	searched.  
Characters that appear after a `\0'	character  are
not  searched.  Since the strnstr() function is 
a FreeBSD specific API, it should only be used 
when portability is not a concern.
If little is an empty string, big is returned; 
if little occurs nowhere in big, NULL is returned; 
otherwise a pointer to	the first character of 
the first occurrence of little is returned.*/

#include "../includes/libft.h"

char	*ft_strnstr(const char *big,	const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*p;

	i = 0;
	p = (char *)big;
	if (*little == '\0' || little == big)
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		j = 0;
		if (big[i] == little[j])
		{
			while (big[i + j] == little[j] && (i + j) < len)
			{
				if (little [j + 1] == '\0')
					return (p + i);
				j++;
			}
		}
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	const char	*little = "ll";
	const char	*big = "Hello, world!";
	size_t		len = 5;

	printf(" my code: %s\n", ft_strnstr(big, little, len));
	//printf("org code: %d\n", strnstr(big, little, len));
	return (0);
}
*/