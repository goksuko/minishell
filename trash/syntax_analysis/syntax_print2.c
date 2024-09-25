/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_print2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 14:32:19 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/09/25 11:45:10 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

const char	*node_type_to_string(t_node_type type)
{
	static const char	*str[] = {
	[N_COMMAND] = "COMMAND",
	[N_PIPE] = "PIPE",
	};

	if (type != N_COMMAND && type != N_PIPE)
		return ("UNKNOWN");
	return (str[type]);
}
