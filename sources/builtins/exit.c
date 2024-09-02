#include "../../includes/minishell.h"

void	handle_no_args(t_tree **ast, t_env **env_var)
{
	free_tree_env(ast, env_var);
	exit(SUCCESS);
}

void	handle_too_many_args(t_tree **ast, t_env **env_var)
{
	free_tree_env(ast, env_var);
	ft_exit_str_fd(ERROR_TOO_MAY_ARGS, STDERR_FILENO);
}

void	handle_numeric_arg(t_tree **ast, t_env **env_var)
{
	int	exit_code;

	if (arg_is_digit((*ast)->expanded_argument[1]) == false)
	{
		free_tree_env(ast, env_var);
		ft_exit_str_fd(ERROR_NUMERIC_ARG, STDERR_FILENO);
	}
	else
	{
		exit_code = exit_atoi((*ast)->expanded_argument[1], ast, env_var);
		free_tree_env(ast, env_var);
		exit(exit_code);
	}
}

void	ft_exit(t_tree **ast, t_env **env_var)
{
	if ((*ast)->expanded_argument[1] == NULL)
		handle_no_args(ast, env_var);
	else if ((*ast)->expanded_argument[2] != NULL)
		handle_too_many_args(ast, env_var);
	else if ((*ast)->expanded_argument[1] != NULL)
		handle_numeric_arg(ast, env_var);
}
