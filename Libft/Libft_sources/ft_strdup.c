/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 11:31:02 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 12:02:13 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*The  strdup() function returns a pointer to a new 
string which is a duplicate of the string s.  
Memory for the new string is obtained with malloc(3), 
and can be freed with free(3). On success, the strdup() 
function returns a pointer to the duplicated string.  
It returns NULL if insufficient memory was available, 
with  errno  set  to indicate the cause of the error.*/

#include "../includes/libft.h"

char	*ft_strdup(const char *s)
{
	char	*temp;
	size_t	i;

	if (!s)
		return (NULL);
	temp = (char *)malloc((ft_strlen((char *)s) + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	i = 0;
	while (s[i])
	{
		temp[i] = s[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

// char	*ft_strdup(const char *s)
// {
// 	char	*copy;
// 	size_t	i;

// 	copy = malloc(sizeof(char) * ft_strlen(s) + 1);
// 	if (!copy)
// 		return (NULL);
// 	i = 0;
// 	while (s[i] != '\0')
// 	{
// 		copy[i] = s[i];
// 		i++;
// 	}
// 	copy[i] = '\0';
// 	return (copy);
// }
/*
int	main(void)
{
    char	*src = "You did it!";
    char	*p = ft_strdup(src);
	char	*p2 = strdup(src);

    printf("src: %s, address: %p\n", src, src);
    printf("  p: %s, address: %p\n", p, p);
	free(p);
    printf(" p2: %s, address: %p\n", p2, p2);
	free(p2);
	return (0);
}
*/