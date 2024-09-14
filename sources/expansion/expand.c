#include "../../includes/minishell.h"

void	expand_arguments(t_data **shell_data, t_tree **node)
{
	printf("----EXPAND_ARGUMENTS----\n");
	int	i;

	i = 0;
	if ((*node)->argument == NULL)
		return ;
	init_expanded_arguments(node);
	while ((*node)->argument[i] != NULL && (*node)->token_types[i] != NULL)
	{
		printf("Start of while loop within expand_arguments\n");
		printf("token_types[%d]: %s\n", i, (*node)->token_types[i]);
		if (ft_strncmp((*node)->token_types[i], "SINGLE_QUOTES", 13) == 0)
		{
			printf("Token type is T_SINGLE_QUOTES\n");
			printf("argument[%d]: %s\n", i, (*node)->argument[i]);
			(*node)->expanded_argument[i] = s_quotes((*node)->argument[i]);
			if ((*node)->expanded_argument[i] == NULL)
			{
				//free_shell_data(shell_data); // need to write this function
				ft_exit_perror(ERROR_ALLOCATION, "malloc in expand_arguments");
			}
		}
		else if (ft_strncmp((*node)->token_types[i], "DOUBLE_QUOTES", 13) == 0)
			(*node)->expanded_argument[i] = d_quotes(shell_data, (*node)->argument[i]);
		// else if (ft_strncmp((*node)->token_types[i], "T_IDENTIFIER", 12) == 0)
		// 	(*node)->expanded_argument[i] = identifier((*node)->argument[i]);
		else
		{
			printf("argument[%d]: %s\n", i, (*node)->argument[i]);
			(*node)->expanded_argument[i] = ft_strdup((*node)->argument[i]);
			if ((*node)->expanded_argument[i] == NULL)
			{
				free_tree(node);
				ft_exit_perror(ERROR_ALLOCATION, "malloc in expand_arguments");
			}
		}
		printf("expanded_argument[%d]: %s\n", i, (*node)->expanded_argument[i]);
		i++;
	}
	(*node)->expanded_argument[i] = NULL;
	// if ((*node)->redirection != NULL) TO DO LATER!!
	// 	expand_redirection(node);
}

void	expansion(t_data **shell_data, t_tree **node)
{
	printf("----EXPANSION----\n");
	if ((*node)->type == N_PIPE)
	{
		expansion(shell_data, &(*node)->left);
		expansion(shell_data, &(*node)->right);
	}
	else
		expand_arguments(shell_data, node);
}