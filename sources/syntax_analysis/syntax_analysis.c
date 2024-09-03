/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_analysis.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 12:05:14 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/09/03 12:05:14 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
	t_token	*temp;

	temp = *tokens;
	node = init_node(N_COMMAND);
	if (node == NULL)
		return (NULL);
	node->argument = ft_strdup((*tokens)->value);
	if (node->argument == NULL)
		return (free_tree(&node), NULL);
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
	token_types_array(&temp, &node);
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
			return (free_tree(&right), NULL); // dont think this is necessary because right already gets freed in combine_nodes in case of an error!
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
		free_list(&tokens);// I think this pointer gets moved in parsed tokens, so this would mean that not the entire list gets freed 
		ft_exit_str_fd(ERROR_ALLOCATION, STDERR_FILENO);
	}
	free_list(&tokens);// I think this pointer gets moved in parsed tokens, so this would mean that not the entire list gets freed 
	return (abstract_syntax_tree);
}
