/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_lst_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/23 15:22:08 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/09/14 21:17:58 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_token_new(char *str, t_token_type type)
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
	new_token->is_file = false;
	return (new_token);
}

void	ft_print_tokens(t_token *tokens) // Only for testing purposes
{
	int	i;

	i = 1;
	while (tokens != NULL)
	{
		printf("Token number: %d\n", i);
		printf("Value: %s\n", tokens->value);
		printf("Token type: %s\n", token_type_to_string(tokens->type));
		printf("Is file: %d\n", tokens->is_file);
		tokens = tokens->next;
		i++;
	}
}

t_token	*init_list(void)
{
	t_token	*lst;

	lst = (t_token *)malloc(sizeof(t_token));
	if (lst == NULL)
		return (NULL);
	lst->type = T_UNKNOWN;
	lst->value = NULL;
	lst->next = NULL;
	lst->prev = NULL;
	lst->is_file = false;
	return (lst);
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
