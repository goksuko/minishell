/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_count.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/04 13:55:44 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/11/10 20:20:34 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_non_whitespace(char *line, int *i)
{
	while (line[*i] && !is_whitespace(line[*i]) && !is_meta(line[*i]))
		(*i)++;
}

void	skip_token(char *line, int *i)
{
	if (is_quote(line[*i]))
		skip_quotes(line, i);
	else if (is_meta(line[*i]))
		skip_meta(&line[*i], i);
	else
		skip_non_whitespace(line, i);
}

int	count_tokens(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line && line[i])
	{
		skip_whitespace(line, &i);
		if (!line[i])
			break ;
		count++;
		skip_token(line, &i);
	}
	return (count);
}
