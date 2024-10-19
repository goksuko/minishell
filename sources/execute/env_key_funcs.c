/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_key_funcs.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 23:04:41 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/19 23:05:06 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	key_rules(char c, int index)
{
	if (index == 0)
	{
		if (ft_isalpha(c) || c == '_')
			return (true);
	}
	if (index > 0)
	{
		if (ft_isalnum(c) || c == '_')
			return (true);
	}
	return (false);
}

int	check_key(t_data *data, char *key)
{
	int	i;

	i = 0;
	if (key && key[0] == '\0')
		ft_exit_data_error(data, ERROR_INVALID_IDENTIFIER);
	while (key && key[i])
	{
		if (!key_rules(key[i], i))
			ft_exit_data_error(data, ERROR_INVALID_IDENTIFIER);
		i++;
	}
	return (EXIT_SUCCESS);
}
