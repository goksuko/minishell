/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:29:51 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 12:01:54 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*The atoi() function converts the initial portion 
of the string pointed to by nptr to int. 
isspace() checks for white-space characters. 
space, form-feed ('\f'), newline ('\n'), 
carriage return ('\r'), horizontal tab ('\t'), 
and vertical tab ('\v').*/

static int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	if (nptr[i] != '\0')
	{
		while (ft_isspace(nptr[i]) == 1)
			i++;
		if (nptr[i] == '-')
			sign = -1;
		if (nptr[i] == '-' || nptr[i] == '+')
			i++;
		while (nptr[i] >= '0' && nptr[i] <= '9')
		{
			nb = (10 * nb) + (nptr[i] - '0');
			i++;
		}
	}
	return (sign * nb);
}
/*
int		main(int argc, char *argv[])
{
	if (argc > 1)
		printf("%d\n", ft_atoi(argv[1]));
	return (0);
}
*/
