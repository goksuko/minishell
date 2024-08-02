/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_tokens.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/02 15:34:08 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/08/02 15:34:08 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_quotes(char *line, int i, char quote_char)
{
	while (line[i] != '\0' && line[i] != quote_char)
		i++;
	if (line[i] == quote_char) // not sure about this
		i++;
	return (i);
}

char	*substring_from_quote(char *line, int *i)
{
	char	*substring;
	int		j;
	char	quote_char;

	quote_char = line[*i];
	j = *i;
	while (line[*i] != '\0' && line[*i] != quote_char)
		i++;
	if (line[*i] == quote_char)
	{
		substring = malloc((*i - j + 1) * sizeof(char));
		if (substring == NULL)
			return (NULL);
		substring = ft_strcpy(substring, &line[j], *i - j);
		i++;
		return (substring);
	}
	return (NULL);
}

char	**split_tokens(char *line, int number_tokens)
{
	char	**tokens;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	tokens = (char **)malloc((number_tokens + 1) * sizeof(char *));
	if (tokens == NULL)
		ft_exit_str_free_fd(ERROR_ALLOCATION, line, STDERR_FILENO);
	while (line[i] != '\0')
	{
		i = skip_whitespace(line, i);
		j = i;
		if (line[i] == '\'' || line[i] == '\"')
			tokens[k] = substring_from_quote(&line[j], &i); //NULL check needed
		else
		{
			while (is_whitespace(line[i]) == false && line[i] != '\0')
				i++;
		}
		if (i > j)
		{
			tokens[k] = malloc((i - j + 1) * sizeof(char));
			if (tokens[k] == NULL)
			{
				while (--k >= 0)
					free(tokens[k]);
				free(tokens);
				return (NULL);
			}
			tokens[k] = ft_strcpy(tokens[k], &line[j], i - j);
			printf("Token %d:%s\n", k, tokens[k]); // to remove later
			k++;
		}
	}
	tokens[k] = NULL;
	return (tokens);
}