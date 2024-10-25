/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_identifier.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 13:29:36 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/25 13:29:36 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_identifier(t_data **data, char *argument)
{
	char	*expanded_str;
	char	*temp;

	expanded_str = NULL;
	temp = ft_strdup(argument);
	if (errno == ENOMEM || temp == NULL)
	{
		free_system_perror(*data, ERROR_ALLOCATION,
			"temp in expand_identifier");
		return (NULL);
	}
	if (dollar_sign_check(temp) == true)
	{
		expanded_str = handle_dollar_sign(*data, temp);
		free (temp);
		if (errno == ENOMEM || expanded_str == NULL)
		{
			free_system_perror(*data, ERROR_ALLOCATION,
				"handle dollar sign in expand_identifier");
			return (NULL);
		}
		return (expanded_str);
	}
	return (temp);
}
