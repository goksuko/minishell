#include "../../includes/minishell.h"

char	*expand_identifier(t_data **shell_data, char *argument)
{
	char	*expanded_str;

	expanded_str = ft_strdup(argument);
	if (expanded_str == NULL)
	{
		free_shell_data(shell_data);
		ft_exit_perror(ERROR_ALLOCATION, "malloc in identifier");
	}
	if (dollar_sign_check(expanded_str) == true)
	{
		expanded_str = handle_dollar_sign(shell_data, expanded_str);
		if (expanded_str == NULL)
		{
			free_shell_data(shell_data);
			ft_exit_perror(ERROR_ALLOCATION, "malloc in handle_dollar_sign");
		}
	}
	return (expanded_str);
}