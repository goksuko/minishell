#include "../../includes/minishell.h"

char	*d_quotes(t_data **data, char *argument)
{
	char	*clean_str;

	clean_str = remove_quotation_marks(argument);
	if (clean_str == NULL)
	{
		free_data(data);
		ft_exit_perror(ERROR_ALLOCATION, "malloc in remove_quotation_marks");
	}
	if (dollar_sign_check(clean_str) == true)
	{
		clean_str = handle_dollar_sign(data, clean_str);
		if (clean_str == NULL)
		{
			free_data(data);
			ft_exit_perror(ERROR_ALLOCATION, "malloc in handle_dollar_sign");
		}
	}
	return (clean_str);
}