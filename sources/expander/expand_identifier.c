#include "../../includes/minishell.h"

char	*expand_identifier(t_data **data, char *argument)
{
	printf("----EXPAND_identifier----\n"); // Only for testing purposes
	char *expanded_str;

	expanded_str = ft_strdup(argument);
	if (errno == ENOMEM || expanded_str == NULL)
	{
		free_system_perror(*data, ERROR_ALLOCATION,
			"expanded_str in expand_identifier");
		return (NULL);
	}
	if (dollar_sign_check(expanded_str) == true)
	{
		expanded_str = handle_dollar_sign(*data, expanded_str);
		if (errno == ENOMEM || expanded_str == NULL)
		{
			free_system_perror(*data, ERROR_ALLOCATION,
				"handle dollar sign in expand_identifier");
			return (NULL);
		}
	}
	return (expanded_str);
}