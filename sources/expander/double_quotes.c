#include "../../includes/minishell.h"

char	*d_quotes(t_data **data, char *argument)
{
	char *clean_str;

	clean_str = remove_quotation_marks(argument);
	if (errno == ENOMEM || clean_str == NULL)
	{
		free_system_perror(*data, ERROR_ALLOCATION,
			"remove quotation marks in d_quotes");
		return (NULL);
	}
	if (dollar_sign_check(clean_str) == true)
	{
		clean_str = handle_dollar_sign(data, clean_str);
		if (errno == ENOMEM || clean_str == NULL)
		{
			free_system_perror(*data, ERROR_ALLOCATION,
				"handle dollar sign in d_quotes");
			return (NULL);
		}
	}
	return (clean_str);
}