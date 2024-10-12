#include "../../includes/minishell.h"

void	execute_shell(t_data *data)
{
	printf("----EXECUTE SHELL----\n");
	int		exit_code;

	// t_env	*env_var;
	// t_tree *ast;

	// ast = data->ast;
	// expansion(&data, &(data->ast), &i);
	//begin_expansion(data); To be uncommented again
	data->exit_code = 0;
	data->nbr_of_pipes = find_pipe_count(data->tokens);
	// printf("nbr_of_pipes: %d\n", data->nbr_of_pipes);
	// while(ast->right != NULL)
	// {
	// 	if (ast->type == N_PIPE)
	// 		execute_pipe(ast, data);
	// 	else
	// 		execute_node(ast, data);
	// 	ast = ast->right;
	// }

	exit_code = create_children(data);
	printf("exit_code: %d\n", exit_code);
	data->exit_code = exit_code;
	// printf("cmds after execution: \n");	
	// printf_array(data->info->cmds);
	free_system(data); // to be replaced with free_data
	// return (exit_code);
}

