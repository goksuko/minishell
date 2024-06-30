/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dec.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/17 20:26:34 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 22:35:23 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_fd.h"

size_t	print_number(int fd, int nb)
{
	static size_t	total;
	char			c;

	total = 0;
	if (nb >= 10)
	{
		print_number(fd, nb / 10);
	}
	if (nb >= 0 && nb <= INT_MAX)
	{
		c = (char)((nb % 10) + '0');
		write(fd, &c, sizeof(char));
		total++;
	}
	return (total);
}

size_t	print_decimal(int fd, int nb)
{
	static size_t	total;

	total = 0;
	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
		total = 11;
	}
	if (nb < 0 && nb > -2147483648)
	{
		write(fd, "-", sizeof(char));
		nb = -1 * nb;
		total++;
	}
	total += print_number(fd, nb);
	return (total);
}

size_t	print_unsign_decimal(int fd, unsigned int nb)
{
	static size_t	total;
	char			c;

	total = 0;
	if (nb >= 10)
	{
		print_unsign_decimal(fd, nb / 10);
	}
	if (nb <= UINT_MAX)
	{
		c = (char)((nb % 10) + '0');
		write(fd, &c, sizeof(char));
		total++;
	}
	return (total);
}
