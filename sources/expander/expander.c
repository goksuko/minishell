#include "../../includes/minishell.h"

void	expand_value(t_data **data, t_token *token, char *type)
{
	printf("----VALUE EXPANSION----\n");

	if (ft_strncmp(type, "SINGLE_QUOTES", 13) == 0)
		token->expanded_value = s_quotes(data, token->value);
	else if (ft_strncmp(type, "DOUBLE_QUOTES", 13) == 0)
		token->expanded_value = d_quotes(data, token->value);
	else if (ft_strncmp(type, "IDENTIFIER", 10) == 0)
		token->expanded_value = expand_identifier(data, token->value);
}

void	expander(t_data **data)
{
	printf("----EXPANDER----\n");
	char	*type;
	t_token	*temp;

	temp = (*data)->tokens;
	while (temp != NULL)
	{
		type = token_type_to_string(temp->type);
		if (ft_strncmp(type, "SINGLE_QUOTES", 13) == 0 || \
		ft_strncmp(type, "DOUBLE_QUOTES", 13) == 0 || ft_strncmp(type, "IDENTIFIER", 10) == 0)
			expand_value(data, temp, type);
		else
			temp->expanded_value = ft_strdup_safe(*data, temp->value);
		temp = temp->next;
	}
}