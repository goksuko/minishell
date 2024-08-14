#include "../includes/minishell.h"

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

char	*create_substr_and_update_token_start(char *line, \
		int *token_start, int *token_len)
{
	new_token_start(line, token_start);
	*token_len = len_new_token(line, *token_start);
	return (create_substr(&line[*token_start], *token_len));
}
