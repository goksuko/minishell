#include "../../includes/minishell.h"

void	execute_node(t_data *shell_data)
{
	printf("----EXECUTE NODE----\n");
	int		exit_code;

	printf("initilaization is done\n\n*******\n\n");
	exit_code = create_children(shell_data);
	printf("exit_code: %d\n", exit_code);
	shell_data->exit_code = exit_code;
}

void	execute_shell(t_data *shell_data)
{
	printf("----EXECUTE SHELL----\n");

	// t_env	*env_var;
	// t_tree *ast;

	// ast = shell_data->ast;
	// expansion(&shell_data, &(shell_data->ast), &i);
	//begin_expansion(shell_data); To be uncommented again
	shell_data->exit_code = 0;
	shell_data->nbr_of_pipes = find_pipe_count(shell_data->line);
	printf("nbr_of_pipes: %d\n", shell_data->nbr_of_pipes);
	// while(ast->right != NULL)
	// {
	// 	if (ast->type == N_PIPE)
	// 		execute_pipe(ast, shell_data);
	// 	else
	// 		execute_node(ast, shell_data);
	// 	ast = ast->right;
	// }

	if (shell_data->nbr_of_pipes == 0)
		execute_node(shell_data);
	else
		shell_data->exit_code = pipes(shell_data);
}

int	pipes(t_data *shell_data)
{
	int		exit_code;

	ft_printf("pipes\n");
	exit_code = create_children(shell_data);
	printf("exit_code: %d\n", exit_code);
	shell_data->exit_code = exit_code;
	free_system(shell_data); // to be replaced with free_shell_data
	return (exit_code);
}

