/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_array_list.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 16:03:29 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/27 11:52:48 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**create_token_array(t_data *data, char *line)
{
	int		number_tokens;
	char	**tokens;

	number_tokens = count_tokens(line);
	tokens = (char **)ft_calloc(number_tokens + 1, sizeof(char *));
	if (errno == ENOMEM || tokens == NULL)
	{
		free_system_perror(data, ERROR_ALLOCATION,
			"tokens in create_token_array");
		return (NULL);
	}
	tokens = split_tokens(line, number_tokens, tokens);
	if (errno == ENOMEM || tokens == NULL)
	{
		ft_free_matrix(tokens);
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
		return (ft_free_matrix(tokens), NULL);
	// head->is_head = true;
	current = head;
	i++;
	while (tokens[i] != NULL)
	{
		current->next = init_new_token(tokens[i], token_type_check(tokens[i]),
				token_count);
		if (current->next == NULL)
			return (ft_free_matrix(tokens), NULL);
		current->next->prev = current;
		current = current->next;
		i++;
	}
	ft_free_matrix(tokens);
	return (head);
}

t_token	*create_token_list(t_data *data, char **token_array)
{
	t_token	*token_lst;
	int		token_count;

	token_count = count_tokens(data->line);
	token_lst = array_to_list(token_array, token_count);
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
