/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 10:37:09 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 12:02:16 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*Allocates (with malloc(3)) and returns a substring
from the string ’s’.
The substring begins at index ’start’ and is of
maximum size ’len’.*/

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (!s)
		return (0);
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}
/*
int	main(void)
{
	char			*s = "Hello, world!";
	unsigned int	start = 3;
	size_t			len = 5;

	printf("%s\n", ft_substr(s, start, len));
	return (0);
}
*/

/*
Error in test 1: ft_substr("", 0, 0): expected: ""
Error in test 2: ft_substr("", 0, 1): expected: ""
Error in test 3: ft_substr("", 1, 1): expected: ""
Error in test 4: ft_substr("hola", 4294967295, 0): expected: ""
Error in test 5: ft_substr("hola", 0, 18446744073709551615): expected: "hola"
Error in test 6: ft_substr("hola", 4294967295, 18446744073709551615): 
expected: ""
Error in test 7: ft_substr("hola", 0, 0): expected: ""
Error in test 8: ft_substr("hola", 0, 1): expected: "h"
Error in test 9: ft_substr("hola", 0, 3): expected: "hol"
Error in test 10: ft_substr("hola", 0, 4): expected: "hola"
Error in test 11: ft_substr("hola", 0, 5): expected: "hola"
Error in test 12: ft_substr("hola", 2, 0): expected: ""
Error in test 13: ft_substr("hola", 2, 1): expected: "l"
Error in test 14: ft_substr("hola", 2, 2): expected: "la"
Error in test 15: ft_substr("hola", 2, 3): expected: "la"
Error in test 16: ft_substr("hola", 2, 30): expected: "la"
Error in test 17: ft_substr("hola", 3, 0): expected: ""
Error in test 18: ft_substr("hola", 3, 1): expected: "a"
Error in test 19: ft_substr("hola", 3, 2): expected: "a"
Error in test 20: ft_substr("hola", 4, 0): expected: ""
Error in test 21: ft_substr("hola", 4, 1): expected: ""
Error in test 22: ft_substr("hola", 4, 20): expected: ""
Error in test 23: ft_substr("hola", 5, 2): expected: ""
*/