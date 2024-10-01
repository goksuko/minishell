#include "../../includes/minishell.h"

void print_env(t_env *env)
{
	while (env != NULL)
	{
		printf("key: %s", env->key);
		printf("=");
		printf("value: %s\n", env->value);
		env = env->next;
	}
}

int	ft_env(char **cmds, t_data *shell_data)
{
	t_env	*env;
	int		return_value;

	env = shell_data->env_list;
	if (cmds[0] == NULL)
	{
		print_env(env);
		return_value = SUCCESS;
	}
	else
		return_value = ERROR_NO_FILE_DIR;
	return (return_value);
}