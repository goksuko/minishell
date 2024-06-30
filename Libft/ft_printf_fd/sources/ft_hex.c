/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hex.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/17 20:26:18 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 22:35:23 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_fd.h"

size_t	print_hexadecimal(int fd, unsigned int hexa)
{
	char			*letters;
	static size_t	total;

	total = 0;
	letters = "0123456789abcdef";
	if (hexa >= 16)
	{
		print_hexadecimal(fd, hexa / 16);
	}
	total += write(fd, &letters[hexa % 16], 1);
	return (total);
}

size_t	print_upp_hexadecimal(int fd, unsigned int hexa)
{
	char			*letters;
	static size_t	total;

	total = 0;
	letters = "0123456789ABCDEF";
	if (hexa >= 16)
	{
		print_upp_hexadecimal(fd, hexa / 16);
	}
	total += write(fd, &letters[hexa % 16], 1);
	return (total);
}

size_t	pointer_helper(int fd, unsigned long int hexa)
{
	char			*letters;
	static size_t	total;

	total = 0;
	letters = "0123456789abcdef";
	if (hexa >= 16)
	{
		pointer_helper(fd, hexa / 16);
	}
	total += write(fd, &letters[hexa % 16], 1);
	return (total);
}

size_t	print_pointer(int fd, unsigned long int nb)
{
	static size_t	total;

	if (nb == 0)
	{
		print_string(fd, "(nil)");
		return (5);
	}
	print_string(fd, "0x");
	total = pointer_helper(fd, nb);
	total = 2 + total;
	return (total);
}
