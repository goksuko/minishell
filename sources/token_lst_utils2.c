#include "../includes/minishell.h"

void	free_list(t_token *tokens)
{
	t_token	*temp;

	while (tokens != NULL)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->value);
		free(temp);
	}
}

void	free_list_array_exit(t_token *tokens_lst, char **array)
{
	free_2d_array(array);
	free_list(tokens_lst);
	ft_exit_str_fd(ERROR_ALLOCATION, STDERR_FILENO);
}