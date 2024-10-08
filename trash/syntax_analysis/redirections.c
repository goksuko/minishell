/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 14:32:10 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/09/23 18:24:08 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	append_new_redir_node(t_redirection **list, t_redirection *new)
{
	t_redirection	*current;

	if (new == NULL)
		return ;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	current = *list;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	new->prev = current;
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

// t_redirection	*init_redirection(t_tree **tree, t_token **token)
t_redirection	*init_redirection(t_token **token)
{
	t_redirection	*redirection;

	redirection = (t_redirection *)malloc(sizeof(t_redirection));
	if (redirection == NULL)
		return (NULL);
	redirection->redirection_type = check_redirection_type((*token)->type);
	redirection->here_doc_fd = -1;
	if ((*token)->next != NULL && (*token)->next->type == T_IDENTIFIER)
	{
		redirection->value = ft_strdup((*token)->next->value);
		if (redirection->value == NULL)
			return (free(redirection), NULL);
	}
	else
	{
		free(redirection);
		//free_list_tree_syntax_exit(token, tree); free entire shell data as well!
	}
	return (redirection);
}

// void	handle_redirection(t_redirection **redirection_lst, \
// 		t_token **token, t_tree **node)
void	handle_redirection(t_redirection **redirection_lst, \
		t_token **token)
{
	printf("----HANDLE REDIRECTION----\n");
	t_redirection	*new_redirection;

	new_redirection = init_redirection(token); //also add node perhaps
	// if (new_redirection == NULL)
	// 	free_list_tree_alloc_exit(token, node); free entire shell data as well!
	next_token(token);
	append_new_redir_node(redirection_lst, new_redirection);
}
