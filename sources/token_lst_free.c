#include "../includes/minishell.h"

void	free_list(t_token **tokens)
{
	t_token	*temp;
	t_token	*current;

	current = *tokens;
	if (current == NULL)
		return ;
	while (current != NULL)
	{
		free(current->value);
		temp = current->next;
		free(current);
		current = temp;
	}
}

void	free_list_line_exit(t_token **tokens_lst, char *line)
{
	printf("----Free list line exit----\n"); // erase later
	free(line);
	free_list(tokens_lst);
	ft_exit_str_fd(ERROR_ALLOCATION, STDERR_FILENO);
}

void	free_line_exit(char *line)
{
	printf("----Free line exit----\n"); // erase later
	free(line);
	ft_exit_str_fd(ERROR_ALLOCATION, STDERR_FILENO);
}
