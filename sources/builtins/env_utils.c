#include "../../includes/minishell.h"

	void	free_env(t_env **env_var)
	{
		t_env	*current;
		t_env	*next;

		current = *env_var;
		while (current != NULL)
		{
			next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			current = next;
		}
		*env_var = NULL;
	}