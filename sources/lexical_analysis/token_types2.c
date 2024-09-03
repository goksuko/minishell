/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_types2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 14:32:39 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/09/03 14:32:39 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_type	check_single_quotes(char *token)
{
	if (ft_strncmp(token, "\'", 1) == 0)
		return (T_SINGLE_QUOTES);
	return (T_UNKNOWN);
}

t_token_type	check_double_quotes(char *token)
{
	if (ft_strncmp(token, "\"", 1) == 0)
		return (T_DOUBLE_QUOTES);
	return (T_UNKNOWN);
}
