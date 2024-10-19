#include "../../includes/minishell.h"

char	*s_quotes(t_data **data, char *argument)
{
	char *clean_str;

	clean_str = remove_quotation_marks(argument);
	if (errno == ENOMEM || clean_str == NULL)
		free_system_perror(*data, ERROR_ALLOCATION,
			"remove quotation marks in s_quotes");
	return (clean_str);
}