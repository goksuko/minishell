#include "../../includes/minishell.h"

char	*expand_identifier(t_data **data, char *argument)
{
	printf("----EXPAND_identifier----\n"); // Only for testing purposes
	char	*expanded_str;

	expanded_str = ft_strdup(argument);
	if (expanded_str == NULL)
	{
		free_data(data);
		ft_exit_perror(ERROR_ALLOCATION, "malloc in expand identifier");
	}
	if (dollar_sign_check(expanded_str) == true)
	{
		expanded_str = handle_dollar_sign(data, expanded_str);
		if (expanded_str == NULL)
		{
			free_data(data);
			ft_exit_perror(ERROR_ALLOCATION, "malloc in handle_dollar_sign");
		}
	}
	return (expanded_str);
}