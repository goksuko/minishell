#include "../includes/minishell.h"

t_token_type	check_single_quotes(char *token)
{
	if (ft_strncmp(token, "\'", 1) == 0)
		return (SINGLE_QUOTES);
	return (UNKNOWN);
}

t_token_type	check_double_quotes(char *token)
{
	if (ft_strncmp(token, "\"", 1) == 0)
		return (DOUBLE_QUOTES);
	return (UNKNOWN);
}
