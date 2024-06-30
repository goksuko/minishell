/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstiter.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 17:01:44 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 12:02:08 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*Iterates the list ’lst’ and applies the function
’f’ on the content of each node.*/

#include "../includes/libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
