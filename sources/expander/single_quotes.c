#include "../../includes/minishell.h"

char	*s_quotes(t_data **data, char *argument)
{
	char	*clean_str;

	clean_str = remove_quotation_marks(argument);
	if (clean_str == NULL)
	{
		free_data(data);
		ft_exit_perror(ERROR_ALLOCATION, "malloc in remove_quotation_marks");
	}
	return (clean_str);
}