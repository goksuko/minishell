#include "../../includes/minishell.h"

// t_env	*ft_envp_node(t_data *shell_data, char *envp)
t_env	*ft_envp_node(char *envp_i)
{
	int		first_eq;
	t_env	*new_node;

	first_eq = find_first_eq(envp_i);
	// new_node = create_node(shell_data, envp, first_eq);
	new_node = create_node(envp_i, first_eq);
	return (new_node);
}

int	find_first_eq(char *envp_i)
{
	int	i;

	i = 0;
	while (envp_i && envp_i[i] && envp_i[i] != '=')
		i++;
	if (envp_i[i] == '\0')
		return (0);
	return (i);
}

t_env	*ft_new_node(char *key, char *value)
{
	t_env	*node;

	node = ft_calloc(sizeof(t_env), 1);
	if (errno == ENOMEM || node == NULL)
		ft_exit_perror(1, "node in ft_new_node");
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

// int	find_data_if_no_pos(t_data *shell_data, char *envp, char **key, char **value)
int	find_data_if_no_pos(char *envp_i, char **key, char **value)
{
	*key = ft_substr(envp_i, 0, ft_strlen(envp_i));
	if (errno == ENOMEM || key == NULL)
		ft_exit_perror(1, "key in find data");
	// if (check_key(*key, ""))
	if (check_key(*key))
		return (free(*key), EXIT_FAILURE);
	*value = NULL;
	return (EXIT_SUCCESS);
}

// t_env	*create_node(t_data *shell_data, char *envp, int pos)
t_env	*create_node(char *envp_i, int pos)
{
	char	*key;
	char	*value;

	if (pos)
	{
		key = ft_substr(envp_i, 0, pos);
		if (errno == ENOMEM || key == NULL)
			ft_exit_perror(1, "key in create node");
		// if (check_key(key, ""))
		if (check_key(key))
			return (free(key), NULL);
		value = ft_substr(envp_i, pos + 1, ft_strlen(envp_i));
		if (errno == ENOMEM || value == NULL)
		{
			free(key);
			ft_exit_perror(1, "value in create node");
		}
	}
	else
	{
		if (find_data_if_no_pos(envp_i, &key, &value))
		// if (find_data_if_no_pos(shell_data, envp, &key, &value))
			return (NULL);
	}
	return (ft_new_node(key, value));
}