/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/17 19:26:05 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/07/05 22:56:08 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_fd.h"

static size_t	do_type_helper(int fd, char t, va_list args)
{
	static size_t	total;

	total = 0;
	if (t == 'x')
		total += print_hexadecimal(fd, va_arg(args, unsigned int));
	else if (t == 'X')
		total += print_upp_hexadecimal(fd, va_arg(args, unsigned int));
	else if (t == 'l')
		total += print_long(fd, va_arg(args, long long));
	else if (t == '%' || t == '\0')
		total += write(fd, "%", sizeof(char));
	else if (t != '%')
	{
		total += write(fd, "%", sizeof(char));
		total += write(fd, &t, sizeof(char));
	}
	return (total);
}

static size_t	do_type(int fd, char t, va_list args)
{
	static size_t	total;

	total = 0;
	if (t == 'c')
		total += print_char(fd, va_arg(args, int));
	else if (t == 's')
		total += print_string(fd, va_arg(args, void *));
	else if (t == 'p')
		total += print_pointer(fd, va_arg(args, unsigned long int));
	else if (t == 'i' || t == 'd')
		total += print_decimal(fd, va_arg(args, int));
	else if (t == 'u')
		total += print_unsign_decimal(fd, va_arg(args, unsigned int));
	else
		total += do_type_helper(fd, t, args);
	return (total);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	unsigned int	i;
	char			*s;
	va_list			args;
	int				total;

	va_start(args, format);
	total = 0;
	if (!format)
		return (-1);
	s = (char *)format;
	i = 0;
	while (format && s[i] != 0)
	{
		if (s[i] != '%')
			total += write(fd, &s[i], sizeof(char));
		else
		{
			total += do_type(fd, s[i + 1], args);
			i++;
		}
		i++;
	}
	va_end(args);
	return (total);
}

int	ft_printf(const char *format, ...)
{
	unsigned int	i;
	char			*s;
	va_list			args;
	int				total;

	va_start(args, format);
	total = 0;
	if (!format)
		return (-1);
	s = (char *)format;
	i = 0;
	while (format && s[i] != 0)
	{
		if (s[i] != '%')
			total += write(STDOUT_FILENO, &s[i], sizeof(char));
		else
		{
			total += do_type(STDIN_FILENO, s[i + 1], args);
			i++;
		}
		i++;
	}
	va_end(args);
	return (total);
}
