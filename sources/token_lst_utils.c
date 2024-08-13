/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_lst_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/23 15:22:08 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/07/23 15:22:08 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*ft_token_new(char *str, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token) * 1);
	if (new_token == NULL)
		return (NULL);
	new_token->value = str;
	new_token->type = type;
	return (new_token);
}

// void	ft_token_lst_add_back(t_token **tokens, t_token *new_token)
// {
// 		t_token	*temp;
// 		t_token	*current;

// 		if (*tokens == NULL)
// 		{
// 			*tokens = new_token;
// 			return ;
// 		}
// 		current = *tokens;
// 		temp = ft_token_last(*tokens);
// 		new_token->next = NULL;
// 		new_token->prev = current;
// }

// t_token	*ft_token_last(t_token *token)
// {
// 	if (token == NULL)
// 		return (NULL);
// 	while (token->next != NULL)
// 		token = token->next;
// 	return (token);
// }

void	ft_print_tokens(t_token *tokens)
{
	int	i;

	i = 1;
	while (tokens != NULL)
	{
		printf("Token: %d\n", i);
		printf("Value: %s\n", tokens->value);
		tokens = tokens->next;
		i++;
	}
}


t_token	*init_list(void)
{
	t_token	*lst;

	lst = (t_token *)malloc(sizeof(t_token));
	if (lst == NULL)
		return (NULL);
	lst->type = TOKEN_UNKNOWN;
	lst->value = NULL;
	lst->next = NULL;
	lst->prev = NULL;
	lst->head = lst;
	lst->tail = lst;
	return (lst);
}