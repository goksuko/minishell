/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   single_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 13:38:37 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/25 13:38:37 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*s_quotes(t_data **data, char *argument)
{
	char	*clean_str;

	clean_str = remove_quotation_marks(argument);
	if (errno == ENOMEM || clean_str == NULL)
		free_system_perror(*data, ERROR_ALLOCATION,
			"remove quotation marks in s_quotes");
	return (clean_str);
}
