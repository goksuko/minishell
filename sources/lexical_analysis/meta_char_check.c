/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   meta_char_check.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/02 15:18:43 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/19 13:01:38 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdbool.h>

int	quote_closed_check(t_data *data, char *line, int i, char quote)
{
	int	j;

	j = i;
	while (line[j] != '\0' && line[j] != quote)
		j++;
	if (line[j] == '\0')
	{
		free_system_error(data, ERROR_QUOTE);
		j = -10;
	}
	return (j);
}

bool	further_meta_check(char *line, int i, char meta)
{
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (false);
	else
	{
		if (meta == '>' && line[i] == '>' && line[i + 1] != '\0')
			return (true);
		if (meta == '>' && line[i] != '\0')
			return (true);
		if (meta == '<' && line[i] == '<' && line[i + 1] != '\0')
			return (true);
		if (meta == '<' && line[i] != '\0')
			return (true);
		if (meta == '|' && line[i] != '\0')
			return (true);
		if (meta == '|' && line[i] == '|')
			return (false);
	}
	return (false);
}

bool	meta_character_check(t_data *data, char *line)
{
	int	i;
	int	closed_quote;

	i = 0;
	while (line[i] != '\0')
	{
		skip_whitespace(line, &i);
		if (is_quote(line[i]) == true)
		{
			closed_quote = quote_closed_check(data, line, i, line[i]);
			if (closed_quote != -10)
				i = closed_quote;
			else
				return (false);
		}
		if (is_meta(line[i]) == true)
		{
			if (further_meta_check(line, i + 1, line[i]) == false)
				return (false);
		}
		i++;
	}
	return (true);
}
