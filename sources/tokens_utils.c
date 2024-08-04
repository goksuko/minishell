/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/02 15:17:39 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/08/04 15:42:00 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_quotes(char *line, int i)
{
	char	quote;

	quote = line[i];
	printf("%c\n", quote);
	i++;
	while (line[i] != '\0' && line[i] != quote)
	{
		printf("%c\n", line[i]);
		i++;
	}
	// if (line[i] != '\0' && line[i] == quote)
	// 	i++;
	printf("\n");
	printf("\n");
	return (i);
}

char	*ft_strcpy(char *dest, char *src, int len)
{
	int	i;

	i = 0;
	while(src[i] != '\0' && len != 0)
	{
		dest[i] = src[i];
		i++;
		len--;
	}
	dest[i] = '\0';
	return (dest);
}

int skip_whitespace(char *line, int i)
{
    while (is_whitespace(line[i]) == true && line[i] != '\0')
        i++;
    return (i);
}

bool	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}

bool	is_meta(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (true);
	return (false);
}

int	skip_meta(char *line, int i, char meta)
{
	i++;
	if (line[i] == meta)
		i++;
	return (i);
}