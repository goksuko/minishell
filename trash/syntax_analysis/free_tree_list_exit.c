/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_tree_list_exit.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 14:32:04 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/09/23 18:16:29 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tree(t_tree **tree)
{
	t_tree	*tmp;

	while (*tree != NULL)
	{
		tmp = (*tree)->right;
		free_redirection_list(&(*tree)->redirection);
		free_array((*tree)->argument);
		free_array((*tree)->token_types);
		free(*tree);
		*tree = tmp;
	}
}

void	free_redirection_list(t_redirection **redirection)
{
	t_redirection	*tmp;

	while (*redirection != NULL)
	{
		tmp = (*redirection)->next;
		free((*redirection)->value);
		free(*redirection);
		*redirection = tmp;
	}
}

