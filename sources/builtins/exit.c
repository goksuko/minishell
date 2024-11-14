/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 13:46:13 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/25 13:46:13 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_numeric_arg(char *exit_code, t_data *data)
{
	int	return_value;

	return_value = -1;
	if (errno == ENOMEM || arg_is_digit(exit_code) == false)
	{
		free_system_error(data, ERROR_NUMERIC_ARG);
		return (ERROR_NUMERIC_ARG);
	}
	else
	{
		return_value = exit_atoi(exit_code, data);
		if (return_value == SUCCESS)
		{
			free_system(data); // CORRECT? TBC
			exit(data->exit_code);
		}
	}
	return (return_value);
}

int	ft_exit(char **cmds, t_data *data)
{
	if (cmds[0] == NULL)
	{
		free_system(data);
		exit(SUCCESS);
	}
	else if (errno == ENOMEM || (cmds != NULL && cmds[1] != NULL))
	{
		free_system_error(data, ERROR_TOO_MANY_ARGS);
		return (ERROR_TOO_MANY_ARGS);
	}
	else if (cmds != NULL && cmds[1] == NULL)
		return (handle_numeric_arg(cmds[0], data));
	return (SUCCESS);
}
