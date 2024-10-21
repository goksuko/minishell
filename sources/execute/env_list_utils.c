/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_list_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 22:59:22 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/21 10:31:00 by akaya-oz      ########   odam.nl         */
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
		if (!ft_strncmp("SHELL", env->key, 5))
		{
			free(env->value);
			env->value = cwd;
			return ;
		}
		env = env->next;
	}
	env_list = &start;
	free(cwd);
	return ;
}

char	*take_path_from_env(t_data *data, t_env **env)
{
	char	*path;

	path = NULL;
	while (*env)
	{
		if (!ft_strncmp("PATH", (*env)->key, 4))
		{
			path = ft_strdup((*env)->value);
			if (path == NULL)
				ft_exit_data_perror(data, ERROR_ALLOCATION,
					"path in update_path");
			break ;
		}
		(*env) = (*env)->next;
	}
	if (!path)
		path = ft_strdup("");
	if (path == NULL)
		ft_exit_data_perror(data, ERROR_ALLOCATION, "path in update_path");
	return (path);
}

void	update_path(t_data *data)
{
	t_env	*env;
	char	*path;

	env = data->env_list;
	path = data->path;
	if (path)
		free(path);
	path = NULL;
	data->path = take_path_from_env(data, &env);
	return ;
}

char	*ft_get_env(t_env *env_list, char *key)
{
	t_env	*temp;

	temp = env_list;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key)) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}
