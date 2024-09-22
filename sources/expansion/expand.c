#include "../../includes/minishell.h"

char	*create_arg_str(t_data **shell_data, t_tree **node, char *expanded_args)
{
	int		i;
	char	*expanded_arg;
	char	*temp;

	i = 0;
	while ((*node)->argument[i] != NULL && (*node)->token_types[i] != NULL)
	{
		expanded_arg = expand_argument(shell_data, *node, i);
		temp = ft_strjoin(expanded_args, expanded_arg);
		free(expanded_arg);
		if (temp == NULL)
		{
			free(expanded_args);
			free_shell_data(shell_data);
			ft_exit_perror(ERROR_ALLOCATION, "malloc in add_redirection");
		}
		expanded_args = temp;
		if ((*node)->argument[i + 1] != NULL)
			expanded_args = add_space_to_str(shell_data, expanded_args);
		i++;
	}
	return (expanded_args);
}

char	*expand_arguments(t_data **shell_data, t_tree **node)
{
	char	*expanded_args;

	expanded_args = ft_strdup("");
	if (expanded_args == NULL)
	{
		free_shell_data(shell_data);
		ft_exit_perror(ERROR_ALLOCATION, "malloc in expand_arguments");
	}
	expanded_args = create_arg_str(shell_data, node, expanded_args);
	if ((*node)->redirection != NULL)
		expanded_args = add_redirection_to_cmd(shell_data, node, expanded_args);
	return (expanded_args);
}

void	expansion(t_data **shell_data, t_tree **node, int *i)
{
	if (*node == NULL)
		return ;
	if ((*node)->type == N_PIPE)
	{
		expansion(shell_data, &(*node)->left, i);
		expansion(shell_data, &(*node)->right, i);
	}
	else
		(*shell_data)->expanded_cmds[(*i)++] = \
			expand_arguments(shell_data, node);
}

void	begin_expansion(t_data *shell_data)
{
	int	i;

	i = 0;
	init_expanded_cmds(&shell_data);
	expansion(&shell_data, &(shell_data->ast), &i);
	printf("---Expansion done! expanded_cmds: \n"); // debugging
	printf_array(shell_data->expanded_cmds); // only for debugging purposes
}
