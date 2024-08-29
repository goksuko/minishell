#include "../../includes/minishell.h"

void	init_env_var(t_env **env_var)
{
	(*env_var)->key = NULL;
	(*env_var)->value = NULL;
	(*env_var)->next = NULL;
}

void	execute_shell(t_tree **ast, t_env **env_var)
{
	init_env_var(env_var);
	if ((*ast)->type == N_COMMAND)
	{
		if (is_builtin((*ast)->argument[0]) == true)
			execute_builtin((*ast)->expanded_argument, env_var);
		// else
		// 	execute_command((*ast)->expanded_argument, env_var);
	}
	// else if ((*ast)->type == N_PIPE)
	// 	execute_pipe(ast, env_var);
}