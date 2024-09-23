#include "../../includes/minishell.h"

t_env	*init_env_list_node(void)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->key = NULL;
	new->value = NULL;
	new->next = NULL;
	return (new);
}

char	*extract_key(char *envp_i)
{
	int		i;
	char	*key;

	i = 0;
	while (envp_i[i] != '=' && envp_i[i] != '\0')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (key == NULL)
		return (NULL);
	ft_strlcpy(key, envp_i, i + 1);
	return (key);
}

char	*extract_value(char *envp_i)
{
	int		i;
	char	*value;

	i = 0;
	while (envp_i[i] != '=' && envp_i[i] != '\0')
		i++;
	value = malloc(sizeof(char) * (ft_strlen(envp_i) - i));
	if (value == NULL)
		return (NULL);
	ft_strlcpy(value, envp_i + i + 1, ft_strlen(envp_i) - i);
	return (value);
}

void	init_env_list(t_data *shell_data, char **envp)
{
	int		i;
	t_env	*new;

	i = 1;
	new = init_env_list_node();
	if (new == NULL)
	{
		free_shell_data(&shell_data);
		ft_exit_perror(ERROR_ALLOCATION, "malloc in init_env_list");
	}
	shell_data->env_list = new;
	while (envp[i])
	{
		new->key = extract_key(envp[i]);
		// NULL Check
		new->value = extract_value(envp[i]);
		// NULL Check
		if (envp[i + 1])
		{
			new->next = init_env_list_node();
			if (new->next == NULL)
			{
				//free_prev_nodes(shell_data->env_list);
				ft_exit_perror(ERROR_ALLOCATION, "malloc in init_env_list");
			}
			new = new->next;
		}
		i++;
	}
}