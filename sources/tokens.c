/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/22 15:18:43 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/08/15 12:05:51 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_characters(char *line)
{
	int	i;
	int	wrong_char;

	i = 0;
	wrong_char = 0;
	while (line && line[i])
	{
		if (line[i] == '\\' || line[i] == ';')
			wrong_char++;
		i++;
	}
	if (wrong_char)
		ft_exit_str_free_fd((ERROR_WRONG_CHAR), line, STDERR_FILENO);
	return ;
}

void	array_to_list(t_token **token_lst, char **tokens)
{
	t_token	*head;
	t_token	*prev;
	t_token	*new_token;
	int		i;

	i = 0;
	head = ft_token_new(tokens[i], token_type_check(tokens[i]));
	if (head == NULL)
		free_list_array_exit(head, tokens);
	prev = head;
	i++;
	while (tokens[i] != NULL)
	{
		new_token = ft_token_new(tokens[i], token_type_check(tokens[i]));
		if (new_token == NULL)
			free_list_array_exit(head, tokens);
		new_token->prev = prev;
		prev->next = new_token;
		prev = new_token;
		i++;
	}
	prev->next = NULL;
	*token_lst = head;
}

char	**create_token_array(char *line)
{
	int		number_tokens;
	char	**tokens;

	number_tokens = count_tokens(line);
	tokens = (char **)malloc((number_tokens + 1) * sizeof(char *));
	if (tokens == NULL)
		ft_exit_str_free_fd(ERROR_ALLOCATION, line, STDERR_FILENO);
	tokens = split_tokens(line, number_tokens, tokens);
	if (tokens == NULL)
		ft_exit_str_free_fd(ERROR_ALLOCATION, line, STDERR_FILENO);
	return (tokens);
}

t_token	*create_token_list(char **token_array, char *line)
{
	t_token	*token_lst;

	token_lst = init_list();
	if (token_lst == NULL)
	{
		free(line);
		free_array_exit(token_array);
	}
	array_to_list(&token_lst, token_array);
	ft_print_tokens(token_lst);
	check_unclosed_quotes(token_lst);
	return (token_lst);
}

t_token	*lexical_analysis(char *line)
{
	char	**tokens;
	t_token	*token_lst;

	if (line[0] == '\0') // also need to check if only a space is entered
		ft_exit_str_free_fd(ERROR_ALLOCATION, line, STDERR_FILENO);
	check_characters(line);
	if (meta_character_check(line) == false)
		ft_exit_str_free_fd(ERROR_META, line, STDERR_FILENO);
	//free(line); //causes a double free error.. Need to investigate
	tokens = create_token_array(line);
	token_lst = create_token_list(tokens, line);
	return (token_lst); // to be ajdusted
}
