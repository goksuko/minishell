/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   meta_char_check.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/02 15:18:43 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/08/02 15:18:43 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	further_meta_check(char *line, int i, char meta)
{
	printf("Further meta check\n"); // to remove later
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (false);
	else
	{
		if (meta == '>' && line[i] == '>' && line[i + 1] == ' ' && line[i + 1] != '\0') // not sure if +1 works here or if +2 is needed
			return (true);
		if (meta == '>' && line[i] == ' ' && line[i + 1] != '\0')
			return (true);
		if (meta == '<' && line[i] == '<' && line[i + 1] == ' ' && line[i + 1] != '\0') // not sure if +1 works here or if +2 is needed
			return (true);
		if (meta == '<' && line[i] == ' ' && line[i + 1] != '\0')
			return (true);
		if (meta == '|' && line[i] == ' ' && line[i + 1] != '\0')
			return (true);
		if (meta == '|' && line[i] == '|')
			return (false);
	}
	return (false);
}

bool	meta_character_check(char *line)
{
	int		i;
	char	quote;

	i = 0;
	while (line[i] != '\0')
	{
		i = skip_whitespace(line, i);
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i]; // just so quote has the same character and we can compare after 
			while (line[i] != '\0' && line[i] != quote)
				i++;
			if (line[i] == '\0')
				return(false);
		}
		if (line[i] == '>' || line[i] == '<' || line[i] == '|')
		{
			if (further_meta_check(line, i + 1, line[i]) == false)
				return (false);
		}
		i++;
	}
	return (true);
}