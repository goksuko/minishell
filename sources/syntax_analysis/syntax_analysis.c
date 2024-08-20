#include "../../includes/minishell.h"

t_tree	*parse_tokens(t_token **tokens)
{
	t_tree	*node;
	t_tree	*pipe_node;

	node = init_node(N_COMMAND);
	if (node == NULL)
		return (NULL);
	while ((*tokens) != NULL)
	{
		if ((*tokens)->type == T_COMMAND)
		{
			node->argument = ft_strdup((*tokens)->value);
			if (node->argument == NULL)
				return (free(node), NULL);
		}
		else if ((*tokens)->type == T_IDENTIFIER || (*tokens)->type == T_FLAG || \
			(*tokens)->type == T_DOUBLE_QUOTES || (*tokens)->type == T_SINGLE_QUOTES || \
			(*tokens)->type == T_ENV_VARIABLE)
			join_arguments(&node, tokens);
		else if (redirection_check(*tokens) == true)
			handle_redirection(&(node->redirection), tokens, &node);
		else if ((*tokens)->type == T_PIPE)
		{
			free_and_next_token(tokens);
			pipe_node = create_new_node(N_PIPE);
			if (pipe_node == NULL)
				return (free(node), NULL);
			pipe_node->next = parse_tokens(tokens);
			if (pipe_node->next == NULL)
				return (free(node), NULL);
			node->next = pipe_node;
		}
		else if ((*tokens)->type == T_UNKNOWN)
			free_list_tree_syntax_exit(&node, tokens); //unsure if correct - may need to reconsider this approach
		free_and_next_token(tokens);
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