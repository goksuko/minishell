/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 16:07:04 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 12:02:16 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*Applies the function ’f’ to each character of the
string ’s’, and passing its index as first argument
to create a new string (with malloc(3)) resulting
from successive applications of ’f’.*/

#include "../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int				len;
	int				i;
	char			*result;

	len = ft_strlen(s);
	if (s == NULL)
		return (0);
	i = 0;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (0);
	while (i < len)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
char	test_func(unsigned int n, char c)
{
	char	str;

	n = 1;
	str = c + n;
	return (str);
}

int	main(void)
{
	char const	s[] = "Hello";
	char		*result = ft_strmapi(s, test_func);

	printf("%s\n", result);
	return (0);
}
*/