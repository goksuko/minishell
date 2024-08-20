#include "../../includes/minishell.h"

void	free_list_exit(t_token **tokens)
{
	free_list(tokens);
	ft_exit_str_fd(ERROR_ALLOCATION, STDERR_FILENO);
}

void    free_tree(t_tree **tree)
{
    t_tree	*tmp;

    while (*tree != NULL)
    {
        tmp = (*tree)->next;
		free_redirection_list(&(*tree)->redirection);
        free((*tree)->argument);
		free_array((*tree)->expanded_argument);
        free(*tree);
        *tree = tmp;
    }
}

void    free_redirection_list(t_redirection **redirection)
{
	t_redirection	*tmp;

	while (*redirection != NULL)
	{
		tmp = (*redirection)->next;
		free((*redirection)->file);
		free_array((*redirection)->expanded_file);
		free(*redirection);
		*redirection = tmp;
	}
}

void	free_list_tree_alloc_exit(t_token **tokens, t_tree **tree)
{
	free_tree(tree);
	free_list(tokens);
	ft_exit_str_fd(ERROR_ALLOCATION, STDERR_FILENO);
}

void	free_list_tree_syntax_exit(t_tree **tree, t_token **token)
{
	free_tree(tree);
	free_list(token);
	ft_exit_str_fd(ERROR_SYNTAX, STDERR_FILENO);
}