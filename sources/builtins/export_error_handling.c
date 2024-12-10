/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_error_handling.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/26 15:56:25 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/11/26 15:56:25 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_allocation_error_env(t_data *data)
{
	free_system_perror(data, ERROR_ALLOCATION, "substr in export()");
	return (ERROR_ALLOCATION);
}

int	create_new_env_error_handling(t_data *data, char *new_key, char *new_value)
{
	if (new_key != NULL)
		free(new_key);
	if (new_value != NULL)
		free(new_value);
	return (handle_allocation_error_env(data));
}
