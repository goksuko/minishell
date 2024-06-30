/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 12:29:59 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 12:02:09 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*Counts the number of nodes in a list.*/

#include "../includes/libft.h"

int	ft_lstsize(t_list *lst)
{
	int		len;

	len = 0;
	if (lst == NULL)
		return (0);
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

/*
int	main(void)
{
	t_list	*list = ft_lstnew("a");
	t_list	*new = ft_lstnew("g");
	int		len;

	ft_lstadd_front(&list, new);
	printf("  list: %s\n", (char*)list->content);
	len = ft_lstsize(list);
	printf("length: %d\n", len);
	return (0);
}
*/