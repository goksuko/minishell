#include "../../includes/minishell.h"

char	*s_quotes(char *argument)
{
	printf("----S_QUOTES----\n");
	char	*clean_str;

	clean_str = remove_quotation_marks(argument);
	printf("clean string: %s\n", clean_str);
	if (clean_str == NULL)
		return (NULL);
	return (clean_str);
}