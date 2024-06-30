/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_char_string.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/17 20:26:29 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 23:09:44 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_fd.h"

size_t	print_char(int fd, int i)
{
	char			c;
	static size_t	total;

	total = 0;
	c = (char)i;
	total += write(fd, &c, sizeof(char));
	return (total);
}

size_t	print_string(int fd, void *ptr)
{
	static size_t	total;
	char			*str;

	total = 0;
	if (ptr == NULL)
	{
		total += write(fd, "(null)", 6);
	}
	else
	{
		str = (char *)ptr;
		total += ft_strlen(str);
		while (*str != '\0')
		{
			write(fd, str, sizeof(char));
			str++;
		}
	}
	return (total);
}
