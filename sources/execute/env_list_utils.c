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

void	update_shell(t_env **env_list)
{
	t_env	*env;
	t_env	*start;
	char	*cwd;

	start = *env_list;
	printf("start: %s\n", start->value);
	env = *env_list;
	cwd = NULL;
	cwd = getcwd(0, 0);
	printf("cwd: %s\n", cwd);
	while (env)
	{
		if (!ft_strncmp("SHELL", env->key, 5))
		{
			printf("env->value: %s\n", env->value);
			free(env->value);
			env->value = cwd;
			printf("env->value: %s\n", env->value);
			return ;
		}
		env = env->next;
	}
	env_list = &start;
	printf("env_list: %s\n", (*env_list)->value);
	free(cwd);
	return ;
}

void update_path(t_data *shell_data)
{
	t_env	*env;
	char	*path;

	env = shell_data->env_list;
	path = NULL;
	while (env)
	{
		if (!ft_strncmp("PATH", env->key, 4))
		{
			path = env->value;
			break ;
		}
		env = env->next;
	}
	if (!path)
	{
		path = ft_strdup("");
		if (errno == ENOMEM || path == NULL)
			ft_exit_perror(1, "path in update_path");
	}
	shell_data->path = path;
	printf("path: %s\n", shell_data->path);
	return ;
}
