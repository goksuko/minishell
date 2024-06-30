/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_front.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 11:26:04 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 12:02:07 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*Adds the node ’new’ at the beginning of the list.*/

#include "../includes/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}
/*
int	main(void)
{
	t_list	*el1 = ft_lstnew("a");
	t_list	*el2 = ft_lstnew("b");
	t_list	*el3 = ft_lstnew("c");
	t_list	*el4 = ft_lstnew("d");
	t_list	*el5 = ft_lstnew("e");

	printf("\nBEFORE\n");
	printf("el1: %s\n", (char*)el1->content);
	printf("el2: %s\n", (char*)el2->content);
	printf("el3: %s\n", (char*)el3->content);
	printf("el4: %s\n", (char*)el4->content);
	printf("el5: %s\n", (char*)el5->content);
	printf("length el1: %d\n", ft_lstsize(el1));
	printf("length el2: %d\n", ft_lstsize(el2));
	printf("length el3: %d\n", ft_lstsize(el3));
	printf("length el4: %d\n", ft_lstsize(el4));
	printf("length el5: %d\n", ft_lstsize(el5));
	while(el1->next != NULL)
	{
		printf("el1: %s\n", (char *)el1->content);
		el1 = el1->next;
	}
	while(el2->next != NULL)
	{
		printf("el2: %s\n", (char *)el2->content);
		el2 = el2->next;
	}
	while(el3->next != NULL)
	{
		printf("el3: %s\n", (char *)el3->content);
		el3 = el3->next;
	}
	while(el4->next != NULL)
	{
		printf("el4: %s\n", (char *)el4->content);
		el4 = el4->next;
	}
	while(el5->next != NULL)
	{
		printf("el5: %s\n", (char *)el5->content);
		el5 = el5->next;
	}

	printf("\nAFTER\n");

	ft_lstadd_front(&el1, el2);
	ft_lstadd_front(&el2, el3);	
	ft_lstadd_front(&el3, el4);	
	ft_lstadd_front(&el4, el5);	

	// ft_lstadd_front(&el4, el5);
	// ft_lstadd_front(&el3, el4);
	// ft_lstadd_front(&el2, el3);	
	// ft_lstadd_front(&el1, el2);
	
	printf("el1: %s\n", (char*)el1->content);
	printf("el2: %s\n", (char*)el2->content);
	printf("el3: %s\n", (char*)el3->content);
	printf("el4: %s\n", (char*)el4->content);
	printf("el5: %s\n", (char*)el5->content);
	printf("length el1: %d\n", ft_lstsize(el1));
	printf("length el2: %d\n", ft_lstsize(el2));
	printf("length el3: %d\n", ft_lstsize(el3));
	printf("length el4: %d\n", ft_lstsize(el4));
	printf("length el5: %d\n", ft_lstsize(el5));
	while(el1->next != NULL)
	{
		printf("el1: %s\n", (char *)el1->content);
		el1 = el1->next;
	}
	while(el2->next != NULL)
	{
		printf("el2: %s\n", (char *)el2->content);
		el2 = el2->next;
	}
	while(el3->next != NULL)
	{
		printf("el3: %s\n", (char *)el3->content);
		el3 = el3->next;
	}
	while(el4->next != NULL)
	{
		printf("el4: %s\n", (char *)el4->content);
		el4 = el4->next;
	}
	while(el5->next != NULL)
	{
		printf("el5: %s\n", (char *)el5->content);
		el5 = el5->next;
	}
	return (0);
}
*/