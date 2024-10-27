/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_print_env.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 13:46:19 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/27 11:56:36 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env_var(t_env *var, int fd)
{
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(var->key, fd);
	if (var->value != NULL && strcmp(var->value, "") != 0)
	{
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(var->value, fd);
		ft_putstr_fd("\"", fd);
	}
	else if (strchr(var->key, '=') != 0)
		ft_putstr_fd("=\"\"", fd);
	ft_putstr_fd("\n", fd);
}

int	get_list_size(t_env *list)
{
	int	size;

	size = 0;
	while (list != NULL)
	{
		list = list->next;
		size++;
	}
	return (size);
}

t_env	*get_next_var_to_print(t_env *list, t_env *last_printed)
{
	t_env	*next_var;

	next_var = NULL;
	while (list != NULL)
	{
		if (last_printed == NULL || strcmp(list->key, last_printed->key) > 0)
		{
			if (next_var == NULL || strcmp(list->key, next_var->key) < 0)
				next_var = list;
		}
		list = list->next;
	}
	return (next_var);
}

void	print_sorted_env_vars(t_env **env, int fd)
{
	int		total_vars;
	int		i;
	t_env	*last_printed;

	total_vars = get_list_size(*env);
	i = 0;
	last_printed = NULL;
	while (i < total_vars)
	{
		last_printed = get_next_var_to_print(*env, last_printed);
		print_env_var(last_printed, fd);
		i++;
	}
}
