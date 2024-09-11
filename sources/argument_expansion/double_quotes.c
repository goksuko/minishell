#include "../../includes/minishell.h"

// include tilde check for cd and export and unset?

char	*d_quotes(t_tree **node, char *argument)
{
	printf("----D_QUOTES----\n");
	char	*clean_str;
	char	*temp;

	temp = (char *)malloc(sizeof(char) * (ft_strlen(argument) - 1) + 1);
	if (temp == NULL)
	{
		free_tree(node);
		ft_exit_perror(ERROR_ALLOCATION, "malloc in d_quotes");
	}
	temp = ft_strcpy(temp, argument + 1, ft_strlen(argument) - 2);
	printf("temp: %s\n", temp);
	if (dollar_sign_check(node, temp) == true)
		handle_dollar_sign(node, &argument);
	clean_str = remove_quotation_marks(temp);
	if (clean_str == NULL)
	{
		free_tree(node);
		ft_exit_perror(ERROR_ALLOCATION, "malloc in d_quotes");
	}
	free(temp);
	return (clean_str);
}