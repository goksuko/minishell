/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens_utils2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/13 12:24:12 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/08/13 21:02:12 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_2d_array(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
	ft_exit_str_fd(ERROR_ALLOCATION, STDERR_FILENO);
}

void	check_unclosed_quotes(char **tokens)
{
	int		i;
	char	quote;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (is_quote(tokens[i][0]) == true)
		{
			quote = tokens[i][0];
			if ((tokens[i][ft_strlen(tokens[i]) - 1]) != quote)
				ft_exit_str_fd(ERROR_QUOTE, STDERR_FILENO);
		}
		i++;
	}
}