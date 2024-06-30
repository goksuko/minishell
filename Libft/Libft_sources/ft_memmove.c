/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:26:55 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 12:02:11 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*The memmove() function copies n bytes from memory area src to memory 
area dest. The memory areas may overlap: copying takes place as though the 
bytes in src are first copied into a temporary array that does not overlap 
src or dest, and the bytes are then copied from the temporary array to dest.*/

#include "../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (!dst && !src)
		return (dst);
	if (src < dst)
		while (n--)
			d[n] = s[n];
	else
		while (n--)
			*d++ = *s++;
	return (dst);
}
/*
int	main(void)
{
	char a[] = {1, 2, 3, 4, 5, 6, 7};
	char b[] = {1, 2, 3, 4, 5, 6, 7};

	ft_memmove(a + 1, a, 2);
	printf("my code: %d\n", a[0]);
	printf("my code: %d\n", a[1]);
	printf("my code: %d\n", a[2]);
	printf("my code: %d\n", a[3]);
	printf("my code: %d\n", a[4]);
	memmove(b + 1, b, 2);
	printf("org code: %d\n", b[0]);
	printf("org code: %d\n", b[1]);
	printf("org code: %d\n", b[2]);
	printf("org code: %d\n", b[3]);
	printf("org code: %d\n", b[4]);
	return (0);
}
*/