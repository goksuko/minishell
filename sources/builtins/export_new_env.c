/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_new_env.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 13:46:16 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/11/17 15:23:46 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_strcmp(const char *s1, const char *s2)
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

char	*extract_key(char *command)
{
	int		i;
	char	*key;

	i = 0;
	while (command[i] != '=')
		i++;
	key = ft_substr(command, 0, i);
	if (key == NULL)
		return (NULL);
	return (key);
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
