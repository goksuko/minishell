/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 11:14:01 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 12:02:09 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*Allocates (with malloc(3)) and returns a new node.
The member variable ’content’ is initialized with
the value of the parameter ’content’. The variable
’next’ is initialized to NULL.*/

#include "../includes/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*arr_list;

	arr_list = (t_list *)malloc(sizeof(t_list) * 1);
	if (arr_list == 0)
		return (NULL);
	arr_list->content = content;
	arr_list->next = NULL;
	return (arr_list);
}
/*
int	main(void)
{
	char	str[] = "Hello, world!";
	t_list	*list;

	list = ft_lstnew(str);
	printf("content is: %s\n", (char *)list->content);
	return (0);
}
*/