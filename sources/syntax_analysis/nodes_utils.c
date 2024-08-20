#include "../../includes/minishell.h"

// need to fix this function as it creates on big argukment event if there is a pipe or redirection
void	join_arguments(t_tree **node, t_token **token)
{
	if ((*node)->argument == NULL)
	{
		(*node)->argument = ft_strdup((*token)->value);
		if ((*node)->argument == NULL)
			free_list_tree_alloc_exit(token, node);
	}
	else
	{
		(*node)->argument = ft_strjoin((*node)->argument, " ");
		if ((*node)->argument == NULL)
			free_list_tree_alloc_exit(token, node);
		(*node)->argument = ft_strjoin((*node)->argument, (*token)->value);
		if ((*node)->argument == NULL)
			free_list_tree_alloc_exit(token, node);
	}
	//printf("----Argument: %s----\n", (*node)->argument);
}
