#include "../../includes/minishell.h"

void	execute_node(t_tree *ast, t_data *shell_data)
{
	printf("----EXECUTE NODE----\n");
	int		exit_code;
	(void)ast;

	printf("initilaization is done\n\n*******\n\n");
	exit_code = create_children(shell_data);
	printf("exit_code: %d\n", exit_code);
	shell_data->exit_code = exit_code;
}

void	execute_shell(t_data *shell_data)
{
	printf("----EXECUTE SHELL----\n");

	if (shell_data->nbr_of_pipes == 0)
		execute_node(shell_data->ast, shell_data);
	else
		shell_data->exit_code = pipes(shell_data);
}

int	pipes(t_data *shell_data)
{
	int		exit_code;

	ft_printf("pipes\n");
	exit_code = create_children(shell_data);
	printf("exit_code: %d\n", exit_code);
	free_system(shell_data);
	return (exit_code);
}

