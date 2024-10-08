/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 14:32:22 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/09/23 14:50:39 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	next_token(t_token **tokens)
{
	printf("----NEXT TOKEN----\n");
	*tokens = (*tokens)->next;
}

bool	redirection_check(t_token *current)
{
	printf("----REDIRECTION CHECK----\n");
	printf("current->type: %d\n", current->type); // debug
	printf("current->value: %s\n", current->value); // debug
	if (current->type == T_SMALLER || current->type == T_GREATER || \
		current->type == T_DSMALLER || current->type == T_DGREATER)
		return (true);
	return (false);
}

t_tree	*init_node(t_node_type type, t_token **tokens)
{
	printf("----INIT NODE----\n");
	t_tree	*new_node;

	new_node = (t_tree *)malloc(sizeof(t_tree));
	if (new_node == NULL)
		return (NULL);
	new_node->type = type;
	if (type == N_COMMAND)
	{
		new_node->argument = allocate_argument_array(tokens);
		if (new_node->argument == NULL)
			return (free_tree(&new_node), NULL); //check if correct
	}
	else
		new_node->argument = NULL;
	new_node->redirection = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->token_types = NULL;
	return (new_node);
}
