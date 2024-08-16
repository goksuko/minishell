/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_tokens.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/02 15:34:08 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/08/16 12:38:37 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*create_substr(char *line, int len)
{
	char	*substr;

	substr = malloc((len + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	substr = ft_strcpy(substr, line, len);
	if (substr == NULL)
		return (NULL);
	return (substr);
}

void	new_token_start(char *line, int *i)
{
	while (line[*i] != '\0' && is_whitespace(line[*i]) == true)
		(*i)++;
}

int	len_new_token(char *line, int i)
{
	int		j;

	j = 0;
	while (line[i] != '\0' && is_whitespace(line[i]) == true)
		i++;
	j = i;
	if (is_meta(line[j]) == true)
	{
		skip_meta(&line[i], &i);
		return (i - j);
	}
	while (line[i] != '\0' && is_whitespace(line[i]) == false \
			&& is_meta(line[i]) == false)
	{
		if (is_quote(line[i]) == true)
			skip_quotes(line, &i);
		if (line[i] != '\0' && is_whitespace(line[i]) == true)
			break ;
		i++;
	}
	return (i - j);
}

char	**split_tokens(char *line, int number_tokens, char **tokens)
{
	int		token_start;
	int		token_len;
	int		i;

	token_start = 0;
	token_len = 0;
	i = 0;
	while (i < number_tokens)
	{
		token_start = token_start + token_len;
		new_token_start(line, &token_start);
		token_len = len_new_token(line, token_start);
		tokens[i] = create_substr(&line[token_start], token_len);
		if (tokens[i] == NULL)
		{
			free_array(tokens);
			return (NULL);
		}
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}
