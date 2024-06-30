/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 10:56:28 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 12:02:12 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
	}
	if (n < 0 && n > -2147483648)
	{
		ft_putchar_fd('-', fd);
		n = -1 * n;
	}
	if (n >= 10)
	{
		ft_putnbr_fd((n / 10), fd);
	}
	if (n >= 0 && n <= 2147483647)
	{
		ft_putchar_fd(((n % 10) + '0'), fd);
	}
}
/*
int     main(void)
{
        int num;

        num = -2147483648;
        ft_putnbr_fd(num, 1);
        ft_putnbr_fd(15, 1);
        ft_putnbr_fd(156, 1);
        ft_putnbr_fd(-568, 1);
        ft_putnbr_fd(0, 1);
        ft_putnbr_fd(9, 1);
        return (0);
}
*/