/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens_utils2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/13 12:24:12 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/18 13:58:41 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_unclosed_quotes(t_data *data, t_token *token_lst)
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
			{
				free_data(&data);
				ft_exit_str_fd(ERROR_QUOTE, STDERR_FILENO);
			}
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
	while (line && line[i] != '\0')
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
			while (line[i] != '\0' && is_whitespace(line[i]) == false && is_meta(line[i]) == false)
				i++;
		}
		i++;
	}
	return (count);
}

void	check_characters(t_data *data, char *line)
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
	{
		free_data(&data);
		ft_exit_str_fd(ERROR_WRONG_CHAR, STDERR_FILENO);
	}
	return ;
}

bool	line_is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
		i++;
	return (i == 0);
}

bool	line_is_whitespace(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (is_whitespace(line[i]) == true)
			i++;
		else
			return (false);
	}
	return (true);
}
