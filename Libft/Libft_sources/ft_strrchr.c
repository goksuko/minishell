/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:28:30 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 12:02:16 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*The strrchr() function returns a pointer 
to the last occurrence of the character c 
in the string s. The strchr() and strrchr() 
functions return a pointer to the matched 
character or NULL if the character is not found. 
The terminating null byte is considered part 
of the string, so that if c is specified as 
'\0', these functions return a pointer 
to the terminator.*/

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;

	str = (char *)s + ft_strlen(s);
	while (*str != (char)c)
	{
		if (str == s)
		{
			return (NULL);
		}
		str--;
	}
	return (str);
}
/*
int	main(void)
{
	char	*s;
	char	ss[] = "tripouille";
	int		c;

	s = "Hello";
	c = 'l';
	printf("org code:%s\n", strrchr(s, c));
	printf(" my code:%s\n", ft_strrchr(s, c));
	printf("org code:%s\n", strrchr(ss, 't' + 256));
	printf(" my code:%s\n", ft_strrchr(ss, 't' + 256));
	return (0);
}
*/