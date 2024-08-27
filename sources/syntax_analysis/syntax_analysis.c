#include "../../includes/minishell.h"

t_tree	*combine_nodes(t_tree *left, t_tree *right)
{
	t_tree	*node;

	node = create_new_node(N_PIPE);
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
	// next_token(tokens);
	while (((*tokens)->type == T_IDENTIFIER || (*tokens)->type == T_FLAG || \
			(*tokens)->type == T_DOUBLE_QUOTES || (*tokens)->type == T_SINGLE_QUOTES || \
			(*tokens)->type == T_ENV_VARIABLE || redirection_check(*tokens) == true) && (*tokens)->next != NULL)
	{
		if ((*tokens)->type == T_IDENTIFIER || (*tokens)->type == T_FLAG || \
			(*tokens)->type == T_DOUBLE_QUOTES || (*tokens)->type == T_SINGLE_QUOTES || \
			(*tokens)->type == T_ENV_VARIABLE)
			join_arguments(&node, tokens);
		else if (redirection_check(*tokens) == true)
			handle_redirection(&(node->redirection), tokens, &node);
		next_token(tokens);
	}
	return (node);
}

t_tree	*parse_tokens(t_token **tokens, int min_precedence)
{
	printf("----Parse_tokens----\n");
	t_tree	*left;
	t_tree	*right;
	int		numb_precedence;

	left = get_command_node(tokens);
	if (left == NULL)
		return (NULL);
	while ((*tokens)->type == T_PIPE)
	{
		printf("PIPE FOUND\n");
		next_token(tokens);
		if ((*tokens) == NULL)
			return (free(left), NULL);
		if ((*tokens)->type != T_COMMAND)
			free_list_tree_syntax_exit(tokens, &left); //check again for correctness
		printf("Token after PIPE: %s\n", (*tokens)->value);
		numb_precedence = min_precedence + 1;
		right = parse_tokens(tokens, numb_precedence);
		if (right == NULL)
			return (free(left), NULL);
		left = combine_nodes(left, right);
		if (left == NULL)
			return (free_tree(&right), free_tree(&left), NULL); //sure to free left here? unsure
	}
	return (left);
}


t_tree	*syntax_analysis(t_token *tokens)
{
	printf("----SYNTAX ANALYSIS----\n");
	t_tree	*abstract_syntax_tree;

	if (tokens->type != T_COMMAND)
		ft_exit_str_fd(ERROR_SYNTAX, STDERR_FILENO);
	abstract_syntax_tree = parse_tokens(&tokens, 0);
	if (abstract_syntax_tree == NULL)
	{
		free_list(&tokens);
		ft_exit_str_fd(ERROR_ALLOCATION, STDERR_FILENO);
	}
	return (abstract_syntax_tree);
}