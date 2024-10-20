/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/22 15:18:43 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/19 18:52:19 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_redir(t_token *current)
{
	if (current && (current->type == T_SMALLER || current->type == T_GREATER
			|| current->type == T_DSMALLER || current->type == T_DGREATER))
		return (true);
	return (false);
}

bool	is_redir_except_heredoc(t_token *current)
{
	if (current && (current->type == T_SMALLER || current->type == T_GREATER
			|| current->type == T_DGREATER))
		return (true);
	return (false);
}

bool	is_heredoc(t_token *current)
{
	if (current->type == T_DSMALLER)
		return (true);
	return (false);
}

bool	heredoc_inside(t_token *current)
{
	while (current && current->type != T_DSMALLER)
		current = current->next;
	if (current)
		return (true);
	else
		return (false);
}

int	heredoc_position(t_token *current)
{
	int	i;

	i = 0;
	while (current)
	{
		if (current->type == T_DSMALLER)
			return (i);
		while (current && current->type != T_PIPE)
			current = current->next;
		if (current && current->type == T_PIPE)
		{
			i++;
			current = current->next; // to skip the pipe
		}
	}
	if (current == NULL)
		return (-15);
	return (i);
}

bool	is_file_check(t_data *data, t_token *token_lst)
{
	t_token	*current;

	current = token_lst;
	while (current != NULL)
	{
		if (is_redir(current) == true)
			if (define_token_fd(data, current) == false)
				return (false);
		current = current->next;
	}
	return (true);
}

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

t_token	*lexical_analysis(t_data *data, char *line)
{
	char	**tokens;
	t_token	*token_lst;

	if (ft_strncmp(line, " ", 1) == 0 && ft_strlen(line) == 1)
	{
		free_system(data);
		data->exit_code = 0;
		return (NULL);
	}
	if (meta_character_check(data, line) == false)
	{
		free_system_error(data, ERROR_META);
		return (NULL);
	}
	tokens = create_token_array(data, line);
	if (tokens == NULL)
		return (NULL);
	token_lst = create_token_list(data, tokens);
	if (token_lst == NULL)
		return (NULL);
	if (is_file_check(data, token_lst) == false)
		return (NULL);
	return (token_lst);
}
