/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_lst_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/23 15:22:08 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/09/26 21:13:43 by akaya-oz      ########   odam.nl         */
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
	new_token->type = type;
//	new_token->is_file = false;
	new_token->token_count = token_count;
	new_token->prev = NULL;
	new_token->next = NULL;
	new_token->fd_in = -10;
	new_token->fd_out = -10;
	new_token->is_head = false;
	new_token->limiter = NULL;
	return (new_token);
}

void	ft_print_tokens(t_token *tokens) // Only for testing purposes
{
	int	i;

	i = 1;
	while (tokens != NULL)
	{
		printf("===Token number --%d--\n", i);
		printf("Value: %s\n", tokens->value);
		printf("Type: %s\n", token_type_to_string(tokens->type));
//		printf("Is file: %d\n", tokens->is_file);
		if (tokens->limiter)
			printf("Limiter: %s\n", tokens->limiter);
		if (tokens->fd_in != -10)
			printf("Fd_in: %d\n", tokens->fd_in);
		if (tokens->fd_out != -10)
			printf("Fd_out: %d\n", tokens->fd_out);
		tokens = tokens->next;
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
	// type = check_file(token);
	// if (type != T_UNKNOWN)
	// 	return (type);
	return (T_IDENTIFIER);
}
