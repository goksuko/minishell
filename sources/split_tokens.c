/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_tokens.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/02 15:34:08 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/08/14 22:12:49 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*create_new_token(char *substr)
{
	t_token	*new_token;

	new_token = ft_token_new(substr, token_type_check(substr));
	free(substr);
	return (new_token);
}

void	link_new_token(t_token *new_token, t_token *prev)
{
	if (prev != NULL)
		prev->next = new_token;
	new_token->prev = prev;
}

t_token	*create_and_link_token(char *line, t_token *prev)
{
	char		*substr;
	static int	token_start;
	int			token_len;
	t_token		*new_token;

	token_len = 0;
	new_token = NULL;
	substr = create_substr_and_update_token_start(line, \
				&token_start, &token_len);
	if (substr == NULL)
		return (NULL);
	new_token = create_new_token(substr);
	if (new_token == NULL)
		return (NULL);
	link_new_token(new_token, prev);
	token_start = token_start + token_len;
	return (new_token);
}

void	split_tokens(char *line, int number_tokens, t_token **token_lst)
{
	t_token	*head;
	t_token	*prev;
	t_token	*new_token;
	int		i;

	i = 0;
	head = NULL;
	prev = NULL;
	new_token = NULL;
	while (i < number_tokens)
	{
		new_token = create_and_link_token(line, prev);
		printf("Token number: %d\n", i);
		printf("Value: %s\n", new_token->value);
		printf("Token type: %s\n", token_type_to_string(new_token->type));
		if (new_token == NULL)
			free_list_line_exit(&head, line); // unsure about position 
		if (head == NULL)
			head = new_token;
		prev = new_token;
		i++;
	}
	if (prev != NULL)
		prev->next = NULL;
	*token_lst = head;
}
