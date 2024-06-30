/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:27:07 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 12:02:16 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*The strlcpy() function copies up to size - 1 
characters from the NUL-terminated string src to dst, 
NUL-terminating the result.
The strlcpy() function returns the total 
length of the string it tried to create.
That means the length of src.
If dst buffer size is not enough for src, it is truncated 1 
in order to finish src with a null terminator. It makes it sure that 
there will not be an overflow.*/

#include "../includes/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dst == NULL || src == NULL || !size)
		return (src_len);
	while (*src && --size)
		*dst++ = *src++;
	*dst = '\0';
	return (src_len);
}

/*
int	main(void)
{
	char	s[50] = "source text";
	char	d[50];
	size_t	size;

	size = 3;
	printf("before d: %s\n", d);
	printf("ft_strlcpy: %zu\n", ft_strlcpy(d, s, size));
	printf("after d: %s\n", d);
	return (0);
}
*/