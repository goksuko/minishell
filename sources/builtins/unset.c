#include "../../includes/minishell.h"

void unset_env_var(char *key, t_env **env_list)
{
	t_env *temp;
	t_env *prev;

	temp = *env_list;
	prev = NULL;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key)) == 0)
		{
			if (prev == NULL)
				*env_list = temp->next;
			else
				prev->next = temp->next;
			free(temp->key);
			free(temp->value);
			free(temp);
			return;
		}
		prev = temp;
		temp = temp->next;
	}
}

int	ft_unset(char **cmds, t_data *shell_data)
{
	int	i;

	i = 0;
	if (cmds[0] == NULL)
		return (SUCCESS);
	while (cmds[i] != NULL)
	{
		unset_env_var(cmds[i], &shell_data->env_list);
		i++;
	}
	return (SUCCESS);
}