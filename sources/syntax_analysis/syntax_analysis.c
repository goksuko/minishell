/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_analysis.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 12:05:14 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/09/23 15:25:35 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_token(t_tree **node, t_token **tokens, int *i)
{
	printf("----HANDLE TOKEN----\n");
	if ((*tokens)->type == T_IDENTIFIER || (*tokens)->type == T_FLAG || \
		(*tokens)->type == T_DOUBLE_QUOTES || \
		(*tokens)->type == T_SINGLE_QUOTES)
	{
		(*node)->argument[*i] = ft_strdup((*tokens)->value);
		if ((*node)->argument[*i] == NULL)
			return ;
		(*i)++;
	}
	// else if (redirection_check(*tokens) == true)
	// 	handle_redirection(&((*node)->redirection), tokens, node);
	bool redirection = redirection_check(*tokens); // TESTING
	printf("%s\n", redirection ? "true" : "false"); // TESTING
	if (redirection == true) // TESTING
		handle_redirection(&((*node)->redirection), tokens, node); // TESTING
}

t_tree	*get_command_node(t_token **tokens)
{
	printf("----GET COMMAND NODE----\n");
	t_tree	*node;
	t_token	*temp;
	int		i;

	i = 0;
	temp = *tokens;
	node = init_node(N_COMMAND, tokens);
	if (node == NULL)
		return (NULL);
	node->argument[i++] = ft_strdup((*tokens)->value);
	printf("node->argument: %s\n", node->argument[i-1]); // debug
	next_token(tokens);
	while ((*tokens) != NULL && (*tokens)->type != T_PIPE && \
		(*tokens)->type != T_UNKNOWN)
	{
		printf("token->value: %s\n", (*tokens)->value); // debug
		handle_token(&node, tokens, &i);
		next_token(tokens);
	}
	node->argument[i] = NULL;
	token_types_array(&temp, &node);
	return (node);
}

t_tree	*parse_tokens(t_token **tokens)
{
	printf("----PARSE TOKENS----\n");
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

	// if (tokens->type != T_BUILTIN && tokens->type != T_IDENTIFIER) // not sure if necessary to check this
	// {
	// 	ft_printf("token type is not a command, it is %s\n", token_type_to_string(tokens->type));
	// 	// ft_exit_str_fd(ERROR_CMD_NOT_FOUND, STDERR_FILENO);
	// }
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
