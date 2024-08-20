#include "../../includes/minishell.h"

void	join_arguments(t_tree **node, t_token **token)
{
	if ((*node)->argument == NULL)
	{
		(*node)->argument = ft_strdup((*token)->value);
		if ((*node)->argument == NULL)
			free_list_tree_alloc_exit(node, token);
	}
	else
	{
		(*node)->argument = ft_strjoin((*node)->argument, " ");
		if ((*node)->argument == NULL)
			free_list_tree_alloc_exit(node, token);
		(*node)->argument = ft_strjoin((*node)->argument, (*token)->value);
		if ((*node)->argument == NULL)
			free_list_tree_alloc_exit(node, token);
	}
}
