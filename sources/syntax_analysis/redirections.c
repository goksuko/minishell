#include "../../includes/minishell.h"

void	append_new_redir_node(t_redirection **list, t_redirection *new)
{
    t_redirection	*current;

    if (*list == NULL)
    {
        *list = new;
        return ;
    }
    current = *list;
    while (current->next != NULL)
        current = current->next;
    current->next = new;
    new->prev = current; // need to check if double linked given the init_node function below
}

t_redirection_type	check_redirection_type(t_token_type type)
{
	if (type == T_SMALLER)
		return (REDIR_IN);
	else if (type == T_GREATER)
		return (REDIR_OUT);
	else if (type == T_DSMALLER)
		return (REDIR_HEREDOC);
	else if (type == T_DGREATER)
		return (REDIR_APPEND);
	else
		return (REDIR_UNKNOWN);
}

t_redirection	*init_redirection(t_tree **tree, t_token **token, t_redirection *prev)
{
    t_redirection	*redirection;

    redirection = (t_redirection *)malloc(sizeof(t_redirection));
    if (redirection == NULL)
        free_list_tree_exit(tree, token, "ALLOC");
    redirection->redirection_type = check_redirection_type((*token)->type);
    if ((*token)->next->type == T_IDENTIFIER)
    {
        redirection->file = ft_strdup((*token)->next->value);
        if (redirection->file == NULL)
        {
            free(redirection);
            free_list_tree_exit(tree, token, "ALLOC");
        }
    }
    else
    {
        free(redirection);
        free_list_tree_exit(tree, token, "SYNTAX");
    }
    redirection->prev = prev;
    return (redirection);
}

void	handle_redirection(t_redirection **redirection_lst, t_token **token, t_tree **node)
{
	t_redirection	*new_redirection;
	// (*node)->redirection = init_redirection(node, token);
	// if ((*node)->redirection == NULL)
	// 	free_list_tree_exit(node, token);
	new_redirection = init_redirection(node, token);
	append_new_redir_node(redirection_lst, new_redirection); //if somethinge goes wrong before this whole list needs to be freed as well

}


