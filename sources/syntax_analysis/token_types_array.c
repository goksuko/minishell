/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_types_array.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 12:05:00 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/09/23 18:25:15 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_token_type(t_tree **node, t_token **tokens)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = *tokens;
	while (temp != NULL && temp->type != T_PIPE && \
		temp->type != T_UNKNOWN)
	{
		if (redirection_check(temp) == true)
			(*node)->token_types[i++] = ft_strdup(redirection_type_to_string \
			((*node)->redirection->redirection_type));
		else
			(*node)->token_types[i++] = ft_strdup(token_type_to_string \
			(temp->type));
		// if ((*node)->token_types[i - 1] == NULL)
		// 	free_list_tree_alloc_exit(tokens, node); free shell data
		temp = temp->next;
	}
	(*node)->token_types[i] = NULL;
}

int	count_tokens_in_list(t_token **tokens)
{
	int		count;
	t_token	*temp;

	temp = *tokens;
	count = 0;
	while (temp != NULL && temp->type != T_PIPE && \
		temp->type != T_UNKNOWN)
	{
		temp = temp->next;
		count++;
	}
	return (count);
}

void	allocate_token_types_array(t_token **tokens, t_tree **node)
{
	int		array_size;

	array_size = count_tokens_in_list(tokens);
	(*node)->token_types = (char **)malloc((array_size + 1) * sizeof(char *));
	// if ((*node)->token_types == NULL)
	// 	free_list_tree_alloc_exit(tokens, node); free shell data
}

void	token_types_array(t_token **tokens, t_tree **node)
{
	allocate_token_types_array(tokens, node);
	add_token_type(node, tokens);
}
