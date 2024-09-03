/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_lst_free.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 14:32:32 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/09/03 14:32:32 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_list(t_token **tokens)
{
	t_token	*temp;
	t_token	*current;

	current = *tokens;
	if (current == NULL)
		return ;
	while (current != NULL)
	{
		free(current->value);
		temp = current->next;
		free(current);
		current = temp;
	}
}

void	free_list_array_exit(t_token *tokens_lst, char **array)
{
	free_array(array);
	free_list(&tokens_lst);
	ft_exit_str_fd(ERROR_ALLOCATION, STDERR_FILENO);
}
