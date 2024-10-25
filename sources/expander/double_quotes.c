/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   double_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 13:29:08 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/25 13:29:08 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*d_quotes(t_data **data, char *argument)
{
	char	*clean_str;
	char	*expanded_str;

	clean_str = NULL;
	expanded_str = NULL;
	clean_str = remove_quotation_marks(argument);
	if (errno == ENOMEM || clean_str == NULL)
	{
		free_system_perror(*data, ERROR_ALLOCATION,
			"remove quotation marks in d_quotes");
		return (NULL);
	}
	if (dollar_sign_check(clean_str) == true)
	{
		expanded_str = handle_dollar_sign(*data, clean_str);
		free(clean_str);
		if (errno == ENOMEM || expanded_str == NULL)
		{
			free_system_perror(*data, ERROR_ALLOCATION,
				"handle dollar sign in d_quotes");
			return (NULL);
		}
		return (expanded_str);
	}
	return (clean_str);
}
