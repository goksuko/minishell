/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:24:36 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 12:01:59 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_isalpha(int c)
{
	if (c < 'A' || (c > 'Z' && c < 'a') || c > 'z')
		return (0);
	else
		return (1);
}
/*
int	main(void)
{
	int	n;

	n = 't';
	printf("%d\n", ft_isalpha(n));
	printf("%d\n", isalpha(n));
	return (0);
}
*/