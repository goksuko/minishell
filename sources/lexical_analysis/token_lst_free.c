/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_lst_free.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 14:32:32 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/09/25 16:50:11 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_token_list(t_token **tokens)
{
	t_token	*temp;
	t_token	*current;

	current = *tokens;
	if (current == NULL)
		return ;
	while (current != NULL)
	{
		if (current->value)
			free_and_null(&current->value);
		if (current->expanded_value)
			free_and_null(&current->expanded_value);
		if (current->limiter)
			free_and_null(&current->limiter);
		temp = current->next;
		free(current);
		current = temp;
	}
	*tokens = NULL;
}
