/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_long_long.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 11:00:43 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/27 11:06:17 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_fd.h"

size_t	print_number_long(int fd, long long nb)
{
	static size_t	total;
	char			c;

	total = 0;
	if (nb >= 10)
	{
		print_number_long(fd, nb / 10);
	}
	if (nb >= 0 && nb <= LLONG_MAX)
	{
		c = (char)((nb % 10) + '0');
		write(fd, &c, sizeof(char));
		total++;
	}
	return (total);
}

size_t	print_long(int fd, long long nb)
{
	static size_t	total;

	total = 0;
	if (nb < 0 && nb >= -9223372036854775807)
	{
		write(fd, "-", sizeof(char));
		nb = -1 * nb;
		total++;
	}
	total += print_number_long(fd, nb);
	return (total);
}
