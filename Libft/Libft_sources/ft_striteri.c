/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striteri.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 17:01:01 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 12:02:13 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*Applies the function ’f’ on each character of
the string passed as argument, passing its index
as first argument. Each character is passed by
address to ’f’ to be modified if necessary.*/

#include "../includes/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, s + i);
		i++;
	}
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
	char		*result = ft_striteri(s, test_func);

	printf("%s\n", result);
	return (0);
}
*/