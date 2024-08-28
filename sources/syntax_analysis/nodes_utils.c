#include "../../includes/minishell.h"

// need to fix this function as it creates on big argukment event if there is a pipe or redirection
void	join_arguments(t_tree **node, t_token **token)
{
	printf("----Join arguments----\n"); //delete later
	char	*temp;

	if ((*node)->argument == NULL)
	{
		(*node)->argument = ft_strdup((*token)->value);
		if ((*node)->argument == NULL)
			free_list_tree_alloc_exit(token, node);
	}
	else
	{
		temp = (*node)->argument;
		(*node)->argument = ft_strjoin(temp, " ");
		free (temp);
		if ((*node)->argument == NULL)
			free_list_tree_alloc_exit(token, node);
		temp = (*node)->argument;
		(*node)->argument = ft_strjoin(temp, (*token)->value);
		free (temp);
		if ((*node)->argument == NULL)
			free_list_tree_alloc_exit(token, node);
	}
	printf("Argument after joining: %s\n", (*node)->argument); //delete later
}
