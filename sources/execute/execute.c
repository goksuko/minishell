#include "../../includes/minishell.h"

bool cat_inside(t_token *current)
{
	if (current && ft_strncmp(current->value, "cat", 3) == 0)
		return (true);
	return (false);
}

int last_exit_code_checks(int exit_code, t_data *data)
{
	if (exit_code == 1 && cat_inside(data->tokens))
		return (0);
	if (WIFSIGNALED(exit_code))
	{
		if (WTERMSIG(exit_code) == 2)
			return (130);
		if (WTERMSIG(exit_code) == 3)
			return (131);
	}
	return (exit_code);
}

void	execute_shell(t_data *data)
{
	printf("----EXECUTE SHELL----\n");
	int		exit_code;

	data->exit_code = 0;
	data->nbr_of_pipes = find_pipe_count(data->tokens);
	exit_code = create_children(data);
	data->exit_code = last_exit_code_checks(exit_code, data);
	printf("exit_code: %d\n", data->exit_code);
	free_system(data); // to be replaced with free_data
	// return (exit_code);
}

