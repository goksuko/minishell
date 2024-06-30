/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:27:23 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 12:02:13 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*The strlcat() function appends 
the NUL-terminated string src to the end of dst.
It will append at most size - strlen(dst) - 1 bytes, 
NUL-terminating the result.
The strlcpy() and strlcat() functions return 
the total length of the string they tried to create.
For strlcat() that means the initial 
length of dst plus the length of src.*/

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d_size;
	size_t	i;

	i = 0;
	while (dst[i] != '\0' && i < size)
		i++;
	d_size = i;
	while (src[i - d_size] && i + 1 < size)
	{
		dst[i] = src[i - d_size];
		i++;
	}
	if (d_size < size)
		dst[i] = '\0';
	return (d_size + ft_strlen(src));
}
/*
int	main(void)
{
	char	dst[] = "dst";
	//char	dst2[] = "dst";
	char	src[] = "source";
	size_t	size = 2;

	printf("%zu\n", ft_strlcat(dst, src, size));
	printf(" dst became: %s\n", dst);
	// printf("%d\n", strlcat(dst2, src, size));
	// printf("dst2 became: %s\n", dst2);
	return (0);
}
*/