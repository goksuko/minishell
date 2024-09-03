/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nodes_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 14:32:07 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/09/03 14:32:07 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	join_arguments(t_tree **node, t_token **token)
{
	char	*temp;

	if ((*node)->argument == NULL)
	{
		(*node)->argument = ft_strdup((*token)->value);
		if ((*node)->argument == NULL)
			free_list_tree_alloc_exit(token, node);
	}
	else
	{
		temp = (*node)->argument;
		(*node)->argument = ft_strjoin(temp, " ");
		free (temp);
		if ((*node)->argument == NULL)
			free_list_tree_alloc_exit(token, node);
		temp = (*node)->argument;
		(*node)->argument = ft_strjoin(temp, (*token)->value);
		free (temp);
		if ((*node)->argument == NULL)
			free_list_tree_alloc_exit(token, node);
	}
}
