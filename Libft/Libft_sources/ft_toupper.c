/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_toupper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:27:37 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 12:02:16 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*If c is a lowercase letter, toupper() returns 
its uppercase equivalent, if an uppercase 
representation exists in the current locale.
Otherwise, it returns c.
The value returned is that of the 
converted letter, or c if the conversion 
was not possible.*/

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c = c - 32;
	return (c);
}
/*
int	main(void)
{
	int	c;

	c = 'd';
	printf("before: %d\n", c);
	printf(" after: %d\n", ft_toupper(c));
	c = 'd';
	printf("   org: %d\n", toupper(c));
	return (0);
}
*/