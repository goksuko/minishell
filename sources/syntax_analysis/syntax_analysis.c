#include "../../includes/minishell.h"

t_tree	*combine_nodes(t_tree *left, t_tree *right)
{
	t_tree	*node;

	if (left == NULL || right == NULL)
		return (NULL);
	node = init_node(N_PIPE);
	if (node == NULL)
		return (free_tree(&left), free_tree(&right), NULL);
	node->left = left;
	node->right = right;
	return (node);
}

t_tree	*get_command_node(t_token **tokens)
{
	t_tree	*node;

	node = init_node(N_COMMAND);
	if (node == NULL)
		return (NULL);
	node->argument = ft_strdup((*tokens)->value);
	if (node->argument == NULL)
		return (free(node), NULL);
	next_token(tokens);
	while ((*tokens) != NULL && (*tokens)->type != T_PIPE && \
		(*tokens)->type != T_UNKNOWN)
	{
		if ((*tokens)->type == T_IDENTIFIER || (*tokens)->type == T_FLAG || \
		(*tokens)->type == T_DOUBLE_QUOTES || \
		(*tokens)->type == T_SINGLE_QUOTES || (*tokens)->type == T_ENV_VARIABLE)
			join_arguments(&node, tokens);
		else if (redirection_check(*tokens) == true)
			handle_redirection(&(node->redirection), tokens, &node);
		next_token(tokens);
	}
	return (node);
}

t_tree	*parse_tokens(t_token **tokens)
{
	t_tree	*left;
	t_tree	*right;

	left = get_command_node(tokens);
	if (left == NULL)
		return (NULL);
	while ((*tokens) != NULL && (*tokens)->type == T_PIPE)
	{
		next_token(tokens);
		if ((*tokens) == NULL)
			return (free_tree(&left), NULL);
		right = parse_tokens(tokens);
		if (right == NULL)
			return (left);
		left = combine_nodes(left, right);
		if (left == NULL)
			return (free_tree(&right), NULL);
	}
	return (left);
}

t_tree	*syntax_analysis(t_token *tokens)
{
	printf("----SYNTAX ANALYSIS----\n");
	t_tree	*abstract_syntax_tree;

	if (tokens->type != T_COMMAND)
		ft_exit_str_fd(ERROR_SYNTAX, STDERR_FILENO);
	abstract_syntax_tree = parse_tokens(&tokens);
	if (abstract_syntax_tree == NULL)
	{
		free_list(&tokens);
		ft_exit_str_fd(ERROR_ALLOCATION, STDERR_FILENO);
	}
	return (abstract_syntax_tree);
}
