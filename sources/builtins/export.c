/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 13:46:27 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/11/15 11:22:47 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_new_key(char *command)
{
	int	i;

	i = 0;
	while (command[i] != '=' && command[i] != '\0')
		i++;
	return (ft_substr(command, 0, i));
}

char	*get_new_value(char *command, int start)
{
	if (command[start] == '\0')
		return (ft_strdup("")); // NEW
	return (ft_substr(command, start, ft_strlen(command) - start));
}

int	handle_allocation_error_env(t_data *data)
{
	free_system_perror(data, ERROR_ALLOCATION, "substr in export()");
	return (ERROR_ALLOCATION);
}

int	create_new_env(t_data **data, char *command)
{
	char	*new_key;
	char	*new_value;
	int		i;
	t_env	*new_env;

	new_key = get_new_key(command);
	if (errno == ENOMEM || new_key == NULL)
		return (handle_allocation_error_env(*data));
	i = ft_strlen(new_key);
	if (command[i] == '=')
	{
		i++;
		new_value = get_new_value(command, i);
		if (errno == ENOMEM || new_value == NULL)
			return (handle_allocation_error_env(*data));
	}
	else
		new_value = NULL;
	new_env = ft_new_node(*data, new_key, new_value);
	if (errno == ENOMEM || new_env == NULL)
		return (handle_allocation_error_env(*data));
	add_new_env_node(&(*data)->env_list, new_env);
	return (SUCCESS);
}

int	ft_export(char **cmds, t_data *data)
{
	// int	i;
	// int	out_fd;
	// int	return_value;

	// return_value = SUCCESS;
	// out_fd = set_out_fd(data);
	// if (cmds[0] == NULL)
	// 	// print_sorted_env_vars(&data->env_list, out_fd);
	// 	return (return_value);
	// else
	// {
	// 	i = 0;
	// 	while (cmds[i] != NULL)
	// 	{
	// 		if (errno == ENOMEM || verify_key(cmds[i], out_fd) == false)
	// 		{
	// 			free_system_error(data, ERROR_INVALID_IDENTIFIER);
	// 			return (ERROR_INVALID_IDENTIFIER);
	// 		}
	// 		return_value = create_new_env(&data, cmds[i]);
	// 		i++;
	// 	}
	// }
	// return (return_value);

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
