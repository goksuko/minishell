/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_array_list.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 16:03:29 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/11/10 19:23:13 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**create_token_array(t_data *data, char *line)
{
	char	**tokens;

	data->nbr_of_tokens = count_tokens(line);
	tokens = (char **)ft_calloc(data->nbr_of_tokens + 1, sizeof(char *));
	if (errno == ENOMEM || tokens == NULL)
	{
		free_system_perror(data, ERROR_ALLOCATION,
			"tokens in create_token_array");
		return (NULL);
	}
	tokens = split_tokens(line, data->nbr_of_tokens, tokens);
	if (errno == ENOMEM || tokens == NULL)
	{
		free_system_perror(data, ERROR_ALLOCATION, "tokens in split_tokens");
		return (NULL);
	}
	return (tokens);
}

t_token	*array_to_list(char **tokens, int token_count)
{
	t_token	*head;
	t_token	*current;
	int		i;

	i = 0;
	head = init_new_token(tokens[i], token_type_check(tokens[i]), token_count);
	if (head == NULL)
		return (free_matrix(tokens), NULL);
	// head->is_head = true;
	current = head;
	i++;
	while (tokens[i] != NULL)
	{
		current->next = init_new_token(tokens[i], token_type_check(tokens[i]),
				token_count);
		if (current->next == NULL)
			return (free_token_list(&current), free_matrix(tokens), NULL);
		current->next->prev = current;
		current = current->next;
		i++;
	}
	free_matrix(tokens);
	return (head);
}

t_token	*create_token_list(t_data *data, char **token_array)
{
	t_token	*token_lst;

	token_lst = array_to_list(token_array, data->nbr_of_tokens);
	if (errno == ENOMEM || token_lst == NULL)
	{
		free_system_perror(data, ERROR_ALLOCATION,
			"token_lst in array_to_list");
		return (NULL);
	}
	if (check_unclosed_quotes(data, token_lst) == false)
		return (NULL);
	return (token_lst);
}
