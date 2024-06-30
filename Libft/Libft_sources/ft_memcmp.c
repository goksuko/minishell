/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:29:23 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 12:02:10 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*The memcmp() function compares the first n bytes (each interpreted as 
unsigned char) of the memory areas s1 and s2. The  memcmp() function returns 
an integer less than, equal to, or greater than zero if the first n bytes of 
s1 is found, respectively, to be less than, to match, or be greater than the 
first n bytes of s2. For a nonzero return value, the sign is determined by 
the sign of the difference between the first pair of bytes (interpreted as 
unsigned  char)  that differ in s1 and s2. 
If n is zero, the return value is zero.*/

#include "../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (n--)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		if (str1[i] == str2[i])
			i++;
	}
	return (0);
}
/*
int	main(void)
{
	char	s1[] = "Text1";
	char	s2[] = "Text2";

	printf("%d\n", ft_memcmp(s1, s2, 5));
	printf("%d\n", memcmp(s1, s2, 5));
	printf("%d\n", ft_memcmp(s1, s2, 1));
	printf("%d\n", memcmp(s1, s2, 1));
	printf("%d\n", ft_memcmp(s1, s2, 18));
	printf("%d\n", memcmp(s1, s2, 18));
	return (0);
}
*/