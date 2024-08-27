#include "../../includes/minishell.h"

t_tree	*create_new_node(t_node_type type)
{
	t_tree	*new_node;

	new_node = (t_tree *)malloc(sizeof(t_tree));
	if (new_node == NULL)
		return (NULL);
	new_node->type = type;
	return (new_node);
}

void	next_token(t_token **tokens)
{
	*tokens = (*tokens)->next;
}

void	free_and_next_token(t_token **tokens) // not sure if should be used because I am already freeing stuff and maybe I need the tokens later on
{
	t_token	*temp;

	temp = *tokens;
	*tokens = (*tokens)->next;
	free(temp->value);
	free(temp);
}

bool	redirection_check(t_token *current)
{
	if (current->type == T_SMALLER || current->type == T_GREATER || \
		current->type == T_DSMALLER || current->type == T_DGREATER)
		return (true);
	return (false);
}

t_tree	*init_node(t_node_type type)
{
	t_tree	*node;

	node = (t_tree *)malloc(sizeof(t_tree));
	if (node == NULL)
		return (NULL);
	node->type = type;
	node->argument = NULL;
	node->expanded_argument = NULL;
	node->redirection = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
