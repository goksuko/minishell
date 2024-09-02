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

// void	add_token_type(t_tree **node, t_token_type type)
// {
// 	static int	i = 0;

// 	(*node)->token_types[i] = token_type_to_string(type);
// 	i++;
// 	(*node)->token_types[i] = NULL;
// }

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
		{
			// add_token_type(&node, (*tokens)->type);
			join_arguments(&node, tokens);
		}
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
	{
		ft_printf("token type is not a command, it is %s\n", token_type_to_string(tokens->type));
		// ft_exit_str_fd(ERROR_CMD_NOT_FOUND, STDERR_FILENO);

	}
	abstract_syntax_tree = parse_tokens(&tokens);
	if (abstract_syntax_tree == NULL)
	{
		ft_printf("abstract_syntax_tree is NULL\n");
		free_list(&tokens);
		ft_exit_str_fd(ERROR_ALLOCATION, STDERR_FILENO);
	}
	// free_list(&tokens);
	return (abstract_syntax_tree);
}
