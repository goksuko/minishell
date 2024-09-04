/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nodes_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 14:32:07 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/09/04 13:34:37 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tree	*combine_nodes(t_tree *left, t_tree *right)
{
	t_tree	*node;

	if (left == NULL || right == NULL)
		return (NULL);
	node = init_node(N_PIPE, NULL);
	if (node == NULL)
		return (free_tree(&left), free_tree(&right), NULL);
	node->left = left;
	node->right = right;
	return (node);
}

int	count_arguments(t_token **tokens)
{
	int		count;
	t_token	*temp;

	temp = *tokens;
	count = 0;
	while (temp != NULL && temp->type != T_PIPE && \
		temp->type != T_UNKNOWN && redirection_check(*tokens) == false)
	{
		temp = temp->next;
		count++;
	}
	return (count);
}

char	**allocate_argument_array(t_token **tokens)
{
	char	**arguments;

	arguments = (char **)malloc(sizeof(char *) * (count_arguments(tokens) + 1));
	if (arguments == NULL)
		return (NULL);
	return (arguments);
}
