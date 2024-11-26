/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 13:46:27 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/11/21 17:10:58 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_key(char *command)
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
		return (ft_strdup(""));
	return (ft_substr(command, start, ft_strlen(command) - start));
}

bool	check_key_existence(t_data *data, char *key)
{
	t_env	*current;

	current = data->env_list;
	while (current != NULL)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key)) == 0)
			return (true);
		current = current->next;
	}
	return (false);
}

int	handle_key(t_data *data, char *command)
{
	char	*key;

	key = extract_key(command);
	if (errno == ENOMEM || key == NULL)
		return (handle_allocation_error_env(data));
	if (check_key_existence(data, key) == true)
		return (update_env_value(data, key, command));
	else
		return (create_new_env(&data, command, key));
}

int	ft_export(char **cmds, t_data *data)
{
	int		i;
	int		out_fd;
	int		return_value;

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
			handle_key(data, cmds[i]);
			i++;
		}
	}
	return (return_value);
}
