/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens_utils2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/13 12:24:12 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/27 12:06:28 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_unclosed_quotes(t_data *data, t_token *token_lst)
{
	t_token	*current;
	char	quote;

	current = token_lst;
	while (current != NULL)
	{
		if (is_quote(current->value[0]) == true)
		{
			quote = current->value[0];
			if ((current->value[ft_strlen(current->value) - 1]) != quote)
			{
				free_system_error(data, ERROR_QUOTE);
				return (false);
			}
		}
		current = current->next;
	}
	return (true);
}

bool	line_is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i == 0);
}

bool	line_is_whitespace(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (is_whitespace(line[i]) == true)
			i++;
		else
			return (false);
	}
	return (true);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	else
		return (0);
}
