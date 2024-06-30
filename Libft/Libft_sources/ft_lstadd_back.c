/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 16:07:17 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/05/24 12:02:07 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*Adds the node ’new’ at the end of the list.

***In case of the new is empty, it still returns the last list of lst.*/

#include "../includes/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*curr;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	curr = *lst;
	while (curr->next != NULL)
	{
		curr = curr->next;
	}
	curr->next = new;
}
/*
int	main(void)
{
	t_list	*el1 = ft_lstnew("a");
	t_list	*el2 = ft_lstnew("b");
	t_list	*el3 = ft_lstnew("c");
	t_list	*el4 = ft_lstnew("d");
	t_list	*el5 = ft_lstnew("e");
	t_list	*temp;

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
	// while (el1)
	// {
    //   printf("Content: %s\n", (char *)(el1->content));
    //   temp = el1;
    //   el1 = el1 -> next;
    //   free(temp);
	// }
	// while (el2)
	// {
    //   printf("Content: %s\n", (char *)(el2->content));
    //   temp = el2;
    //   el2 = el2 -> next;
    //   free(temp);
	// }
	// while (el3)
	// {->next != NULL
    //   printf("Content: %s\n", (char *)(el3->content));
    //   temp = el3;
    //   el3 = el3 -> next;
    //   free(temp);
	// }

	printf("\nAFTER\n");

	ft_lstadd_back(&el1, el2);
	ft_lstadd_back(&el2, el3);	
	ft_lstadd_back(&el3, el4);	
	ft_lstadd_back(&el4, el5);	

	// ft_lstadd_back(&el4, el5);
	// ft_lstadd_back(&el3, el4);
	// ft_lstadd_back(&el2, el3);	
	// ft_lstadd_back(&el1, el2);
	
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