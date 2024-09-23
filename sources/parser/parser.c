#include "../../includes/minishell.h"

int	ft_count_processes(t_data *shell_data)
{
	int		count;
	t_token	*temp;

	count = 0;
	temp = shell_data->tokens;
	while (temp != NULL)
	{
		if (temp->type == T_PIPE && temp->next == NULL)
		{
			free_shell_data(&shell_data);
			ft_exit_perror(ERROR_SYNTAX, "syntax error near unexpected token '|'");
		}
		count++;
		temp = temp->next;
	}
	return (count + 1);
}

t_parser	*init_parser(t_data *shell_data)
{
	t_parser	*parser;

	parser = (t_parser *)malloc(sizeof(t_parser));
	if (parser == NULL)
		return (NULL);
	parser->tokens = shell_data->tokens;
	parser->num_processes = ft_count_processes(shell_data->tokens);
	return (parser);
}

t_parser	*parser(t_data *shell_data)
{
	t_parser	*parser;

	parser = init_parser(shell_data);
	if (parser == NULL)
	{
		free_shell_data(&shell_data);
		ft_exit_perror(ERROR_ALLOCATION, "malloc in init_parser");
	}
}