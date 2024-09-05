#include "../../includes/minishell.h"

bool	key_rules(char c, int index)
{
	if (index == 0)
	{
		if (ft_isalpha(c) || c == '_')
			return (true);
	}
	if (index > 0)
	{
		if (ft_isalnum(c) || c == '_')
			return (true);
	}
	return (false);
}

// int	check_key(char *key, char *cmd)
int	check_key(char *key)
{
	int		i;
	// char	*new_key;

	i = 0;
	// new_key = NULL;
	if (key && key[0] == '\0')
		ft_exit_str_fd(ERROR_INVALID_IDENTIFIER, STDERR_FILENO);
	while (key && key[i])
	{
		if (!key_rules(key[i], i))
		{
			// new_key = ft_trip_join("`", key, "'");
			// ft_write_error(2, cmd, new_key, "not a valid identifier");
			ft_exit_str_fd(ERROR_INVALID_IDENTIFIER, STDERR_FILENO);
			// free(new_key);
			// return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}