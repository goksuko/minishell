#include "../../includes/minishell.h"

char	*expand_identifier(t_data **data, char *argument)
{
	printf("----EXPAND_identifier----\n"); // Only for testing purposes
	char	*expanded_str;
	char	*temp;

	expanded_str = NULL;
	temp = ft_strdup(argument);
	if (errno == ENOMEM || temp == NULL)
	{
		free_system_perror(*data, ERROR_ALLOCATION,
			"temp in expand_identifier");
		return (NULL);
	}
	if (dollar_sign_check(temp) == true)
	{
		expanded_str = handle_dollar_sign(*data, temp);
		free (temp);
		if (errno == ENOMEM || expanded_str == NULL)
		{
			free_system_perror(*data, ERROR_ALLOCATION,
				"handle dollar sign in expand_identifier");
			return (NULL);
		}
		return (expanded_str);
	}
	return (temp);
}