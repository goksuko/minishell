/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens_utils2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/13 12:24:12 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/08/16 12:37:10 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_array_exit(char **arrray)
{
	int	i;

	i = 0;
	while (arrray[i] != NULL)
	{
		free(arrray[i]);
		i++;
	}
	free(arrray);
	ft_exit_str_fd(ERROR_ALLOCATION, STDERR_FILENO);
}

void	check_unclosed_quotes(t_token *token_lst)
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
				ft_exit_str_fd(ERROR_QUOTE, STDERR_FILENO);
		}
		current = current->next;
	}
}

int	count_tokens(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		skip_whitespace(line, &i);
		if (line[i] == '\0')
			break ;
		count++;
		if (is_quote(line[i]) == true)
			skip_quotes(line, &i);
		else if (is_meta(line[i]) == true)
			skip_meta(&line[i], &i);
		else if (line[i] != '\0' && is_whitespace(line[i]) == false \
		&& is_quote(line[i]) == false && is_meta(line[i]) == false)
		{
			while (line[i] != '\0' && is_whitespace(line[i]) == false)
				i++;
		}
		i++;
	}
	return (count);
}

void	check_characters(char *line)
{
	int	i;
	int	wrong_char;

	i = 0;
	wrong_char = 0;
	while (line && line[i])
	{
		if (line[i] == '\\' || line[i] == ';')
			wrong_char++;
		i++;
	}
	if (wrong_char)
		ft_exit_str_free_fd((ERROR_WRONG_CHAR), line, STDERR_FILENO);
	return ;
}
