#include "../../includes/minishell.h"

void	free_list_exit(t_token **tokens)
{
	free_list(tokens);
	ft_exit_str_fd(ERROR_ALLOCATION, STDERR_FILENO);
}

void	free_tree(t_tree **tree)
{
    t_tree	*tmp;

    while (*tree != NULL)
    {
        tmp = (*tree)->next;
        free((*tree)->argument);
        free(*tree);
        *tree = tmp;
    }
}

void	free_list_tree_exit(t_token **tokens, t_tree **tree, char *error)
{
	free_list(tokens);
	free_tree(tree);
    if (ft_strncmp(error, "ALLOC", 5) == 0)
	    ft_exit_str_fd(ERROR_ALLOCATION, STDERR_FILENO);
    else if (ft_strncmp(error, "SYNTAX", 6) == 0)
        ft_exit_str_fd(ERROR_SYNTAX, STDERR_FILENO);
}