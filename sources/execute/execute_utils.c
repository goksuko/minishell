#include "../../includes/minishell.h"

void	free_tree_env(t_tree **ast, t_env **env_var)
{
	free_tree(ast);
	free_env(env_var);
}