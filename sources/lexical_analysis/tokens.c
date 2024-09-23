/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/22 15:18:43 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/09/23 18:13:03 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	is_file_check(t_token *token_lst)
{
	t_token	*current;

	current = token_lst;
	while (current != NULL)
	{
		if (is_file(current->value) == true)
			current->is_file = true;
		current = current->next;
	}
}

char	**create_token_array(t_data *shell_data, char *line)
{
	int		number_tokens;
	char	**tokens;

	number_tokens = count_tokens(line);
	tokens = (char **)malloc((number_tokens + 1) * sizeof(char *));
	if (tokens == NULL)
	{
		free_array(tokens);
		free_shell_data(&shell_data);
		ft_exit_str_fd(ERROR_ALLOCATION, STDERR_FILENO);
	}
	tokens = split_tokens(line, number_tokens, tokens);
	if (tokens == NULL)
	{
		free_array(tokens);
		free_shell_data(&shell_data);
		ft_exit_str_fd(ERROR_ALLOCATION, STDERR_FILENO);
	}
	return (tokens);
}

t_token	*array_to_list(char **tokens, int token_count)
{
	t_token	*head;
	t_token	*current;
	int		i;

	i = 0;
	head = ft_token_new(tokens[i], token_type_check(tokens[i]), token_count);
	if (head == NULL)
		return (free_array(tokens), NULL);
	current = head;
	i++;
	while (tokens[i] != NULL)
	{
		current->next = ft_token_new(tokens[i], token_type_check(tokens[i]), token_count);
		if (current->next == NULL)
			return (free_array(tokens), NULL);
		current = current->next;
		i++;
	}
	free_array(tokens);
	return (head);
}

t_token	*create_token_list(t_data *shell_data, char **token_array)
{
	t_token	*token_lst;
	int		token_count;

	token_count = count_tokens(shell_data->line);
	token_lst = array_to_list(token_array, token_count);
	if (token_lst == NULL)
	{
		free_shell_data(&shell_data);
		ft_exit_str_fd(ERROR_ALLOCATION, STDERR_FILENO);
	}
	check_unclosed_quotes(shell_data, token_lst);
	return (token_lst);
}

t_token	*lexical_analysis(t_data *shell_data, char *line)
{
	char	**tokens;
	t_token	*token_lst;

	if (line[0] == '\0' || line_is_empty(line) == true)
	{
		free_shell_data(&shell_data);
		ft_exit_str_fd(ERROR_EMPTY_LINE, STDERR_FILENO);
	}
	check_characters(shell_data, line);
	if (meta_character_check(line) == false)
	{
		free_shell_data(&shell_data);
		ft_exit_str_fd(ERROR_META, STDERR_FILENO);
	}
	tokens = create_token_array(shell_data, line);
	token_lst = create_token_list(shell_data, tokens);
	is_file_check(token_lst);
	return (token_lst);
}

