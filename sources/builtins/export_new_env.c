/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_new_env.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 13:46:16 by vbusekru      #+#    #+#                 */
/*   Updated: 2025/01/13 11:13:25 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

bool	verify_key(char *key, int fd)
{
	if (ft_isalpha(key[0]) == false && key[0] != '_')
	{
		ft_putstr_fd("export: `", fd);
		ft_putstr_fd(key, fd);
		ft_putendl_fd("': not a valid identifier", fd);
		return (false);
	}
	return (true);
}

void	add_new_env_node(t_env **env_list, t_env *new_env)
{
	t_env	*current;

	current = *env_list;
	if (ft_strncmp(new_env->key, current->key, ft_strlen(new_env->key)) < 0)
	{
		new_env->next = current;
		*env_list = new_env;
	}
	else
	{
		current = *env_list;
		while (current->next != NULL && ft_strncmp(current->next->key,
				new_env->key, ft_strlen(new_env->key)) < 0)
			current = current->next;
		new_env->next = current->next;
		current->next = new_env;
	}
}

int	create_new_env(t_data **data, char *command, char *new_key)
{
	char	*new_value;
	int		i;
	t_env	*new_env;

	i = ft_strlen(new_key);
	if (command[i] == '=')
	{
		i++;
		new_value = get_new_value(command, i);
		if (errno == ENOMEM || new_value == NULL)
			return (create_new_env_error_handling(*data, new_key, NULL));
	}
	else
		new_value = NULL;
	new_env = ft_new_node(*data, new_key, new_value);
	if (errno == ENOMEM || new_env == NULL)
		return (create_new_env_error_handling(*data, new_key, new_value));
	add_new_env_node(&(*data)->env_list, new_env);
	free_and_null(&new_key);
	free_and_null(&new_value);
	return (SUCCESS);
}

int	update_env_value(t_data *data, char *key, char *command)
{
	t_env	*current;
	int		i;

	current = data->env_list;
	while (current != NULL)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key)) == 0)
		{
			i = ft_strlen(key);
			if (command[i] == '=')
			{
				i++;
				free(current->value);
				current->value = get_new_value(command, i);
				if (errno == ENOMEM || current->value == NULL)
					return (create_new_env_error_handling(data, key, NULL));
			}
			break ;
		}
		current = current->next;
	}
	free(key);
	return (SUCCESS);
}
