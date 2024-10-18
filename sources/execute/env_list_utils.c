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

void update_path(t_data *data)
{
	t_env	*env;
	char	*path;

	env = data->env_list;
	path = data->path;
	if (path)
		free(path);
	path = NULL;
	while (env)
	{
		if (!ft_strncmp("PATH", env->key, 4))
		{
			path = ft_strdup_safe(data, env->value);
			break ;
		}
		env = env->next;
	}
	if (!path)
		path = ft_strdup_safe(data, "");
	data->path = path;
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
