#include "../../includes/minishell.h"

// only print the list if there is a key with a value. e.g. PATH=bskjd. 
// However, if there is simply the key "VANESSA" with no other value, then it should not be printed

void print_env(t_env *env)
{
	while (env != NULL && env->value != NULL)
	{
		printf("%s", env->key);
		printf("=");
		printf("%s\n", env->value);
		env = env->next;
	}
}

int	ft_env(char **cmds, t_data *data)
{
	t_env	*env;
	int		return_value;

	env = data->env_list;
	if (cmds[0] == NULL)
	{
		print_env(env);
		return_value = SUCCESS;
	}
	else
		return_value = ERROR_NO_FILE_DIR;
	return (return_value);
}