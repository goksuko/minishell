#include "../../includes/minishell.h"

char	*redir_value(t_redirection_type type)
{
	if (type == REDIR_IN)
		return (ft_strdup("<"));
	else if (type == REDIR_OUT)
		return (ft_strdup(">"));
	else if (type == REDIR_APPEND)
		return (ft_strdup(">>"));
	else if (type == REDIR_HEREDOC)
		return (ft_strdup("<<"));
	else
		return (NULL);
}

char	*add_redirection(t_data **shell_data, t_tree **node)
{
	char	*redirection;
	char	*temp;

	redirection = redir_value((*node)->redirection->redirection_type);
	if (redirection == NULL)
	{
		free_shell_data(shell_data);
		ft_exit_perror(ERROR_ALLOCATION, "malloc in add_redirection");
	}
	if ((*node)->redirection->value != NULL)
	{
		redirection = add_space_to_str(shell_data, redirection);
		temp = ft_strjoin(redirection, (*node)->redirection->value);
		if (temp == NULL)
		{
			free(redirection);
			free_shell_data(shell_data);
			ft_exit_perror(ERROR_ALLOCATION, "malloc in add_redirection");
		}
		free(redirection);
		redirection = temp;
	}
	return (redirection);
}

char	*add_redirection_to_cmd(t_data **shell_data, \
		t_tree **node, char *expanded_args)
{
	char	*redirection;
	char	*temp;

	expanded_args = add_space_to_str(shell_data, expanded_args);
	redirection = add_redirection(shell_data, node);
	temp = ft_strjoin(expanded_args, redirection);
	free(redirection);
	free(expanded_args);
	if (temp == NULL)
	{
		free_shell_data(shell_data);
		ft_exit_perror(ERROR_ALLOCATION, "malloc in add_redirection_to_cmd");
	}
	return (temp);
}