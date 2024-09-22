#include "../../includes/minishell.h"

int	ast_size(t_tree *ast)
{
    if (ast ==  NULL)
        return (0);
    if (ast->type == N_COMMAND)
        return (1 + ast_size(ast->left) + ast_size(ast->right));
    else
        return (ast_size(ast->left) + ast_size(ast->right));
}

void	init_expanded_cmds(t_data **shell_data)
{
	printf("----INIT_EXPANDED_ARGUMENTS----\n");
	int		count;

	count = ast_size((*shell_data)->ast);
	printf("count: %d\n", count);
	(*shell_data)->expanded_cmds = (char **)malloc(sizeof(char *) * (count + 1));
	if ((*shell_data)->expanded_cmds == NULL)
	{
		free_shell_data(shell_data);
		ft_exit_perror(ERROR_ALLOCATION, "malloc in init_expanded_arguments");
	}
	(*shell_data)->expanded_cmds[count] = NULL;
}

char	*remove_quotation_marks(char *argument)
{
	printf("----REMOVE_QUOTATION_MARKS----\n");
	char	*clean_str;

	clean_str = (char *)malloc(sizeof(char) * ((ft_strlen(argument) - 2) + 1));
	if (clean_str == NULL)
		return (NULL);
	clean_str = ft_strcpy(clean_str, argument + 1, ft_strlen(argument) - 2);
	return (clean_str);
}

char	*expand_argument(t_data **shell_data, t_tree *node, int i)
{
	char	*expanded_arg;

	if (ft_strncmp(node->token_types[i], "SINGLE_QUOTES", 13) == 0)
		expanded_arg = s_quotes(shell_data, node->argument[i]);
	else if (ft_strncmp(node->token_types[i], "DOUBLE_QUOTES", 13) == 0)
		expanded_arg = d_quotes(shell_data, node->argument[i]);
	else if (ft_strncmp(node->token_types[i], "IDENTIFIER", 12) == 0)
		expanded_arg = expand_identifier(shell_data, node->argument[i]);
	else
	{
		expanded_arg = ft_strdup(node->argument[i]);
		if (expanded_arg == NULL)
		{
			free_shell_data(shell_data);
			ft_exit_perror(ERROR_ALLOCATION, "malloc in expand_arguments");
		}
	}
	return (expanded_arg);
}

char	*add_space_to_str(t_data **shell_data, char *str)
{
	char	*temp;

	temp = ft_strjoin(str, " ");
	if (temp == NULL)
	{
		free(str);
		free_shell_data(shell_data);
		ft_exit_perror(ERROR_ALLOCATION, "malloc in add_space_to_str");
	}
	free(str);
	return (temp);
}