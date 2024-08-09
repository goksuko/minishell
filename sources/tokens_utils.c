/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/02 15:17:39 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/08/09 20:01:56 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_quotes(char *line, int *i)
{
	char	quote;

	quote = line[*i];
	(*i)++;
	while (line[*i] != '\0' && line[*i] != quote)
		(*i)++;
}

void	skip_whitespace(char *line, int *i)
{
	while (line[*i] != '\0' && isspace(line[*i]))
		(*i)++;
}

bool	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}

void	skip_meta(char *line, int *i)
{
	if (ft_strncmp(line, ">>", 2) == 0)
		*i += 2;
	else if (ft_strncmp(line, "<<", 2) == 0)
		*i += 2;
	else if (ft_strncmp(line, ">", 1) == 0)
		*i += 1;
	else if (ft_strncmp(line, "<", 1) == 0)
		*i += 1;
	else if (ft_strncmp(line, "|", 1) == 0)
		*i += 1;
}

bool	is_meta(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (true);
	return (false);
}
