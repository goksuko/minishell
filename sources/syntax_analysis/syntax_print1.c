#include "../../includes/minishell.h"

const char	*redirection_type_to_string(t_redirection_type type)
{
	static const char	*str[] = {
	[REDIR_IN] = "REDIR_IN",
	[REDIR_OUT] = "REDIR_OUT",
	[REDIR_APPEND] = "REDIR_APPEND",
	[REDIR_HEREDOC] = "REDIR_HEREDOC",
	[REDIR_UNKNOWN] = "REDIR_UNKNOWN",
	};

	if (type != REDIR_IN && type != REDIR_OUT \
	&& type != REDIR_APPEND && type != REDIR_HEREDOC \
	&& type != REDIR_UNKNOWN)
		return ("UNKNOWN");
	return (str[type]);
}

void	ft_print_redirection(t_redirection *redirection_lst)
{
	int	i;

	i = 1;
	while (redirection_lst != NULL)
	{
		printf("Redirection number: %d\n", i);
		printf("Redirection type: %s\n", \
		redirection_type_to_string(redirection_lst->redirection_type));
		if (redirection_lst->file != NULL)
			printf("File: %s\n", redirection_lst->file);
		if (redirection_lst->expanded_file != NULL)
		{
			printf("Expanded file: \n");
			printf_array(redirection_lst->expanded_file);
		}
		redirection_lst = redirection_lst->next;
		i++;
	}
}

void	ft_print_ast(t_tree *ast, int *node_count)
{
	if (ast == NULL)
		return ;
	printf("Node number: %d\n", *node_count);
	printf("Node type: %s\n", node_type_to_string(ast->type));
	if (ast->argument != NULL)
		printf("Argument: %s\n", ast->argument);
	if (ast->expanded_argument != NULL)
	{
		printf("Expanded argument: \n");
		printf_array(ast->expanded_argument);
	}
	if (ast->redirection != NULL)
	{
		printf("Redirection: \n");
		ft_print_redirection(ast->redirection);
	}
	(*node_count)++;
	if (ast->type == N_PIPE)
	{
		if (ast->left != NULL)
		{
			printf("----Left Node----\n");
			ft_print_ast(ast->left, node_count);
		}
		if (ast->right != NULL)
		{
			printf("----Right Node----\n");
			ft_print_ast(ast->right, node_count);
		}
	}
}

void	print_ast(t_tree *ast)
{
	int	node_count;

	node_count = 1;
	printf("----Printing AST----\n");
	ft_print_ast(ast, &node_count);
}
