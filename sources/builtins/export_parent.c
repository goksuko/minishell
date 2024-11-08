/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_parent.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 13:46:27 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/25 16:40:13 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_parent_export(char **cmds, t_data *data)
{
	int	i;
	int	out_fd;
	int	return_value;

	return_value = SUCCESS;
	out_fd = set_out_fd(data);
	if (cmds[0] == NULL)
		print_sorted_env_vars(&data->env_list, out_fd);
	else
	{
		i = 0;
		while (cmds[i] != NULL)
		{
			if (errno == ENOMEM || verify_key(cmds[i], out_fd) == false)
			{
				free_system_error(data, ERROR_INVALID_IDENTIFIER);
				return (ERROR_INVALID_IDENTIFIER);
			}
			return_value = create_new_env(&data, cmds[i]);
			i++;
		}
	}
	return (return_value);
}
