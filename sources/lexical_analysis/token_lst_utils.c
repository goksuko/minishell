/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_lst_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/23 15:22:08 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/19 13:02:02 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*init_new_token(char *str, t_token_type type, int token_count)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token) * 1);
	if (new_token == NULL)
		return (NULL);
	new_token->value = ft_strdup(str);
	if (new_token->value == NULL)
	{
		free(new_token);
		return (NULL);
	}
	new_token->expanded_value = NULL;
	new_token->type = type;
	new_token->token_count = token_count;
	new_token->prev = NULL;
	new_token->next = NULL;
	new_token->fd_in = -10;
	new_token->fd_out = -10;
	new_token->here_doc_fd = -10;
	new_token->is_head = false; // is this needed and used because I see it was commented out in array_to_list()
	new_token->limiter = NULL;
	return (new_token);
}

void	ft_print_tokens(t_token *tokens) // Only for testing purposes
{
	printf("----PRINT TOKENS----\n");
	int		i;
	t_token	*temp;

	if (tokens == NULL)
	{
		printf("No tokens\n");
		return ;
	}
	i = 1;
	temp = tokens;
	while (temp != NULL)
	{
		printf("===Token number --%d--\n", i);
		if (temp->value != NULL)
			printf("Value: %s\n", temp->value);
		else
			printf("Value: (null)\n");
		if (temp->expanded_value != NULL)
			printf("Expanded value: %s\n", temp->expanded_value);
		else
			printf("Expanded value: (null)\n");
		printf("Token type: %s\n", token_type_to_string(temp->type));
		if (temp->limiter != NULL)
			printf("Limiter: %s\n", temp->limiter);
		else
			printf("Limiter: (null)\n");
		if (temp->fd_in != -10)
			printf("Fd_in: %d\n", temp->fd_in);
		else
			printf("Fd_in: (not set)\n");
		if (temp->fd_out != -10)
			printf("Fd_out: %d\n", temp->fd_out);
		else
			printf("Fd_out: (not set)\n");
		temp = temp->next;
		i++;
	}
}

t_token_type	token_type_check(char *token)
{
	t_token_type	type;

	type = check_command(token);
	if (type != T_UNKNOWN)
		return (type);
	type = check_redirection(token);
	if (type != T_UNKNOWN)
		return (type);
	type = check_pipes(token);
	if (type != T_UNKNOWN)
		return (type);
	type = check_flag(token);
	if (type != T_UNKNOWN)
		return (type);
	type = check_single_quotes(token);
	if (type != T_UNKNOWN)
		return (type);
	type = check_double_quotes(token);
	if (type != T_UNKNOWN)
		return (type);
	return (T_IDENTIFIER);
}
