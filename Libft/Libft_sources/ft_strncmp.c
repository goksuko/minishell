/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:28:58 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 12:02:16 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*The strcmp() function compares the 
two strings s1 and s2. strcmp() returns 
an integer indicating the result of the 
comparison, as follows:
• 0, if the s1 and s2 are equal;
• a negative value if s1 is less than s2;
• a positive value if s1 is greater than s2.
The strncmp() function is similar, except 
it compares only the first (at most) n bytes of s1 and s2.*/

#include "../includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 || *s2) && n--)
		if (*s1++ != *s2++)
			return ((unsigned char)*--s1 - (unsigned char)*--s2);
	return (0);
}
/*
int	main(void)
{
	char	*s1;
	char	*s2;

	s1 = "Hello, world!";
	s2 = "Hello, you!";
	printf("org code: %d\n", strncmp(s1, s2, 3));
	printf(" my code: %d\n", ft_strncmp(s1, s2, 3));
	printf("org code: %d\n", strncmp(s1, s2, 10));
	printf(" my code: %d\n", ft_strncmp(s1, s2, 10));
	printf("org code: %d\n", strncmp("t", "", 0));
	printf(" my code: %d\n", ft_strncmp("t", "", 0));
	printf("org code: %d\n", strncmp("1234", "1235", 3));
	printf(" my code: %d\n", ft_strncmp("1234", "1235", 3));
	printf("org code: %d\n", strncmp("", "1", 0));
	printf(" my code: %d\n", ft_strncmp("", "1", 0));
	printf("org code: %d\n", strncmp("1", "", 0));
	printf(" my code: %d\n", ft_strncmp("1", "", 0));
	printf("org code: %d\n", strncmp("", "1", 1));
	printf(" my code: %d\n", ft_strncmp("", "1", 1));
	printf("org code: %d\n", strncmp("1", "", 1));
	printf(" my code: %d\n", ft_strncmp("1", "", 1));
	return (0);
}
*/