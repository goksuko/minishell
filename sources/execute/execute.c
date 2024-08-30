#include "../../includes/minishell.h"

t_env	*init_env_var(void)
{
	printf("----INIT ENV VAR----\n");
	t_env	*new_env_var;

	new_env_var = (t_env *)malloc(sizeof(t_env));
	if (new_env_var == NULL)
		return (NULL);
	new_env_var->key = NULL;
	new_env_var->value = NULL;
	new_env_var->next = NULL;
	return (new_env_var);
}

void	execute_shell(t_tree **ast)
{
	printf("----EXECUTE SHELL----\n");
	t_env	*env_var;
	
	env_var = init_env_var();
	(*ast)->expanded_argument = ft_split((*ast)->argument, ' '); // only for testing purposes
	if ((*ast)->type == N_COMMAND)
	{
		printf("%s\n", (*ast)->expanded_argument[0]);
		if (is_builtin((*ast)->expanded_argument[0]) == true)
			execute_builtin((*ast)->expanded_argument, &env_var);
		// else
		// 	execute_command((*ast)->expanded_argument, env_var);
	}
	// else if ((*ast)->type == N_PIPE)
	// 	execute_pipe(ast, env_var);
}