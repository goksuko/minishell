// #include "../../includes/minishell.h"

// char	**expansion(char *argument_str)
// {
// 	(void)argument_str;
// }

// void	expand_arguments(t_tree *node)
// {
// 	t_redirection	*temp_redir;

// 	temp_redir = node->redirection;
// 	if (node->argument == NULL)
// 		return ;
// 	node->expanded_argument = expansion(node->argument);
// 	// while (temp_redir != NULL)
// 	// {
// 	// 	if (temp_redir->redirection_type == REDIR_HEREDOC)
// 	// 		//do stuff
// 	// 	else
// 	// 		temp_redir->expanded_file = expansion(temp_redir->file);
// 	// 	temp_redir = temp_redir->next;
// 	// }
// }

// void	init_exec_tree(t_tree *node)
// {
// 	if (node == NULL)
// 		return ;
// 	if (node->type == N_PIPE)
// 	{
// 		init_exec_tree(node->left);
// 		init_exec_tree(node->right);
// 	}
// 	else
// 		expand_arguments(node);
// }