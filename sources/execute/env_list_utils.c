/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 22:59:22 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/11/23 15:59:11 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_prev_nodes(t_env *head)
{
	t_env	*tmp;

	tmp = NULL;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	return ;
}

void	update_shell(t_data *data, t_env **env_list)
{
	t_env	*env;
	t_env	*start;
	char	*cwd;

	start = *env_list;
	env = *env_list;
	cwd = NULL;
	cwd = getcwd(0, 0);
	if (cwd == NULL)
		ft_exit_data_perror(data, ERROR_ALLOCATION, "cwd in update_shell");
	while (env)
	{
		if (ft_strncmp("SHELL", env->key, 5) == 0)
		{
			free_and_null(&env->value);
			env->value = ms_strdup(data, cwd);
			break ;
		}
		env = env->next;
	}
	env_list = &start;
	free_and_null(&cwd);
	return ;
}

char	*take_path_from_env(t_data *data, t_env **env)
{
	char	*path;

	path = NULL;
	while (*env)
	{
		if (ft_strncmp("PATH", (*env)->key, 4) == 0)
		{
			path = ms_strdup(data, (*env)->value);
			break ;
		}
		(*env) = (*env)->next;
	}
	if (!path)
		path = ms_strdup(data, "");
	return (path);
}

void	update_path(t_data *data)
{
	t_env	*env;

	env = data->env_list;
	free_and_null(&data->path);
	data->path = take_path_from_env(data, &env);
	return ;
}

char	*ft_get_env(t_env *env_list, char *key)
{
	t_env	*temp;
	int		key_len;

	temp = env_list;
	key_len = ft_strlen(key);
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key, key_len) == 0
			&& (int)ft_strlen(temp->key) == key_len)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}
