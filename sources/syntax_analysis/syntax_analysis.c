#include "../../includes/minishell.h"

t_tree	*syntax_analysis(t_token *tokens)
{
	t_tree	*tree;
	t_tree	*current;
	t_token	*current_token;

	tree = (t_tree *)malloc(sizeof(t_tree));
	if (tree == NULL)
		return (NULL);
	tree->type = T_UNKNOWN;
	tree->value = NULL;
	tree->prev = NULL;
	tree->next = NULL;
	current = tree;
	current_token = tokens;
	while (current_token != NULL)
	{
		current->type = current_token->type;
		current->value = ft_strdup(current_token->value);
		if (current->value == NULL)
			return (NULL);
		current_token = current_token->next;
		if (current_token != NULL)
		{
			current->next = (t_tree *)malloc(sizeof(t_tree));
			if (current->next == NULL)
				return (NULL);
			current->next->prev = current;
			current = current->next;
		}
	}
	current->next = NULL;
	return (tree);
}