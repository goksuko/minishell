#include "../../includes/minishell.h"

void	init_expanded_arguments(t_tree **node)
{
	printf("----INIT_EXPANDED_ARGUMENTS----\n");
	int		count;

	count = 0;
	while ((*node)->argument[count] != NULL)
		count++;
	(*node)->expanded_argument = (char **)malloc(sizeof(char *) * (count + 1));
	if ((*node)->expanded_argument == NULL)
	{
		free_tree(node);
		ft_exit_perror(ERROR_ALLOCATION, "malloc in init_expanded_arguments");
	}
}

char	*remove_quotation_marks(char *argument)
{
	printf("----REMOVE_QUOTATION_MARKS----\n");
	char	*clean_str;

	clean_str = (char *)malloc(sizeof(char) * ((ft_strlen(argument) - 2) + 1));
	if (clean_str == NULL)
		return (NULL);
	clean_str = ft_strcpy(clean_str, argument + 1, ft_strlen(argument) - 2);
	return (clean_str);
}