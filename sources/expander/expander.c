#include "../../includes/minishell.h"

void	expand_value(t_data **shell_data, t_token *token, char *type)
{
	printf("----VALUE EXPANSION----\n");

	if (ft_strncmp(type, "SINGLE_QUOTES", 13) == 0)
		token->expanded_value = s_quotes(shell_data, token->value);
	else if (ft_strncmp(type, "DOUBLE_QUOTES", 13) == 0)
		token->expanded_value = d_quotes(shell_data, token->value);
	else if (ft_strncmp(type, "IDENTIFIER", 12) == 0)
		token->expanded_value = expand_identifier(shell_data, token->value);
}

void	expander(t_data **shell_data)
{
	printf("----EXPANDER----\n");
	char	*type;
	t_token	*temp;

	temp = (*shell_data)->tokens;
	while (temp != NULL)
	{
		type = token_type_to_string(temp->type);
		if (ft_strncmp(type, "SINGLE_QUOTES", 13) == 0 || \
		ft_strncmp(type, "DOUBLE_QUOTES", 13) == 0 || ft_strncmp(type, "IDENTIFIER", 10) == 0)
			expand_value(shell_data, temp, type);
		else
		{
			temp->expanded_value = ft_strdup(temp->value);
			if (temp->expanded_value == NULL)
			{
				free_shell_data(shell_data);
				ft_exit_perror(ERROR_ALLOCATION, "malloc in expansion");
			}
		}
		temp = temp->next;
	}
}