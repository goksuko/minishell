#include "../../includes/minishell.h"

// Need to implement a recursive descent parser here
// Need to implement a context-free grammar here
// Need to implement an abstract syntax tree here

t_tree	*parse_tokens(t_token **tokens)
{
	t_tree	*node;

	node = new_node(N_COMMAND);
	//properly init tree struct instead of simple new node function ?
	if (node == NULL)
		return (NULL);
	while ((*tokens) != NULL)
	{
		if ((*tokens)->type == T_COMMAND)
		{
			node->argument = ft_strdup((*tokens)->value);
			if (node->argument == NULL)
				return (free(node), NULL); // add error handling here ?
		}
		else if ((*tokens)->type == T_IDENTIFIER || (*tokens)->type == T_FLAG || \
			(*tokens)->type == T_DOUBLE_QUOTES || (*tokens)->type == T_SINGLE_QUOTES)
			join_arguments(&node, &tokens);
		else if ((*tokens)->type == T_PIPE)
			// handle pipes
		else if (redirection_check(*tokens) == true)
			handle_redirection(node->redirection, tokens, &node); // need to implement this function
		else if ((*tokens)->type == T_ENV_VARIABLE)
			// handle env variables
		else if ((*tokens)->type == T_UNKNOWN)
			// handle unknown tokens
		free_and_next_token(&tokens);
	}
	return (node);
}

t_tree	*syntax_analysis(t_token *tokens)
{
	t_tree	*ast;

	ast = parse_tokens(&tokens);
	if (ast == NULL)
	{
		free_list(&tokens);
		ft_exit_str_fd(ERROR_ALLOCATION, STDERR_FILENO);
	}
	return (ast);
}