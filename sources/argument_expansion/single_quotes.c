#include "../../includes/minishell.h"

char	*s_quotes(t_tree **node, char *argument)
{
	printf("----S_QUOTES----\n");
	char	*temp;
	char	*clean_str;

	temp = (char *)malloc(sizeof(char) * (ft_strlen(argument) + 1));
	if (temp == NULL)
	{
		free_tree(node);
		ft_exit_perror(ERROR_ALLOCATION, "malloc in s_quotes");
	}
	temp = ft_strcpy(temp, argument, ft_strlen(argument));
	printf("temp: %s\n", temp);
	clean_str = remove_quotation_marks(temp);
	printf("clean string: %s\n", clean_str);
	if (clean_str == NULL)
	{
		free_tree(node);
		ft_exit_perror(ERROR_ALLOCATION, "malloc in s_quotes");
	}
	free(temp);
	return (clean_str);
}	