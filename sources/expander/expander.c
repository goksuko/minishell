#include "../../includes/minishell.h"

bool	expand_value(t_data **data, t_token *token, char *type)
{
	printf("----VALUE EXPANSION----\n");

	if (ft_strncmp(type, "SINGLE_QUOTES", 13) == 0)
	{
		token->expanded_value = s_quotes(data, token->value);
		if (token->expanded_value == NULL)
			return (false);
	}	
	else if (ft_strncmp(type, "DOUBLE_QUOTES", 13) == 0)
	{
		token->expanded_value = d_quotes(data, token->value);
		if (token->expanded_value == NULL)
			return (false);	}
	else if (ft_strncmp(type, "IDENTIFIER", 10) == 0)
	{
		token->expanded_value = expand_identifier(data, token->value);
		if (token->expanded_value == NULL)
			return (false);
	}
	return (true);
}

bool	expander(t_data **data)
{
	char	*type;
	t_token	*temp;

	temp = (*data)->tokens;
	while (temp != NULL)
	{
		type = token_type_to_string(temp->type);
		if (ft_strncmp(type, "SINGLE_QUOTES", 13) == 0 || \
		ft_strncmp(type, "DOUBLE_QUOTES", 13) == 0 || ft_strncmp(type, "IDENTIFIER", 10) == 0)
		{
			if (expand_value(data, temp, type) == false)
				return (false);
		}
		else
		{
			temp->expanded_value = ft_strdup(temp->value);
			if (temp->expanded_value == NULL)
			{
				free_system_perror(*data, ERROR_ALLOCATION, "temp->expanded_value in expander");
				return (false);
			}
		}
		temp = temp->next;
	}
	return (true);
}