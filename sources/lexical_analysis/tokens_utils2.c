/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens_utils2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/13 12:24:12 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/21 10:55:57 by akaya-oz      ########   odam.nl         */
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

int	count_tokens(char *line)
{
	int	i;
	int	count;
	int loop;

	loop = 0;

	i = 0;
	count = 0;
	while (line && line[i] != '\0')
	{
		skip_whitespace(line, &i);
		if (line[i] == '\0')
			break ;
		count++;
		if (line && line[i] && is_quote(line[i]) == true)
			skip_quotes(line, &i);
		else if (line && line[i] && is_meta(line[i]) == true)
			skip_meta(&line[i], &i);
		else if (line && line[i] && is_whitespace(line[i]) == false
			&& is_quote(line[i]) == false && is_meta(line[i]) == false)
		{
			while (line && line[i] && is_whitespace(line[i]) == false
				&& is_meta(line[i]) == false)
				i++;
		}
		if (line[i] != '\0')
			i++;
		loop++;
	}
	return (count);
}

bool	line_is_empty(char *line)
{
	int	i;

	i = 0;
	// while (line && line[i]) // to be checked if it creates a problem in the program
	while (line[i]) // to be checked if it creates a problem in the program
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
