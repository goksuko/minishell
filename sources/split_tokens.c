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

char	*create_substr(char *line, int *i)
{
	char	*substring;
	int		j;

	j = *i;
	while (line[*i] != '\0' && is_whitespace(line[*i]) == false \
			&& is_quote(line[*i]) == false)
		i++;
	substring = malloc((*i - j + 1) * sizeof(char));
	if (substring == NULL)
		return (NULL);
	substring = ft_strcpy(substring, &line[j], *i - j);
	if (substring == NULL)
		return (NULL);
	return (substring);
}

char	*substring_from_quote(char *line, int *i)
{
	char	*substring;
	int		j;
	char	quote;

	quote = line[*i];
	j = *i;
	while (line[*i] != '\0' && line[*i] != quote)
		i++;
	if (line[*i] == quote)
	{
		substring = malloc((*i - j + 1) * sizeof(char));
		if (substring == NULL)
			return (NULL);
		substring = ft_strcpy(substring, &line[j], *i - j);
		if (substring == NULL)
			return (NULL);
		i++;
		return (substring);
	}
	return (NULL);
}

char	**split_tokens(char *line, int number_tokens)
{
	char	**tokens;
	int		i;
	int		k;

	i = 0;
	k = 0;
	tokens = (char **)malloc((number_tokens + 1) * sizeof(char *));
	if (tokens == NULL)
		ft_exit_str_free_fd(ERROR_ALLOCATION, line, STDERR_FILENO);
	while (line[i] != '\0')
	{
		i = skip_whitespace(line, i);
		printf("Position of i: %d\n", i);
		if (is_quote(line[i]) == true)
		{
			tokens[k] = substring_from_quote(&line[i], &i);
			printf("Position of i: %d\n", i);
		}
		else if (is_quote(line[i]) == false && is_whitespace(line[i]) \
				== false && line[i] != '\0')
		{
			tokens[k] = create_substr(&line[i], &i);
			printf("Position of i: %d\n", i);
		}
		if (tokens[k] == NULL)
		{
			while (k > 0) // Need to check this part again if correct
				free(tokens[k--]);
			free(tokens);
			return (NULL);
		}
		else
			k++;
	}
	tokens[k] = NULL;
	return (tokens);
}
