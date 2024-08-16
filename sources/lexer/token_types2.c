#include "../../includes/minishell.h"

t_token_type	check_single_quotes(char *token)
{
	if (ft_strncmp(token, "\'", 1) == 0)
		return (T_SINGLE_QUOTES);
	return (T_UNKNOWN);
}

t_token_type	check_double_quotes(char *token)
{
	if (ft_strncmp(token, "\"", 1) == 0)
		return (T_DOUBLE_QUOTES);
	return (T_UNKNOWN);
}
