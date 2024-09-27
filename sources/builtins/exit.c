#include "../../includes/minishell.h"

void	handle_no_args(t_data *shell_data)
{
	free_shell_data(&shell_data);
	exit(SUCCESS);
}

void	handle_too_many_args(t_data *shell_data)
{
	free_shell_data(&shell_data);
	ft_exit_str_fd(ERROR_TOO_MANY_ARGS, STDERR_FILENO);
}

void	handle_numeric_arg(char *exit_code, t_data *shell_data)
{
	int	exit_code;

	if (arg_is_digit(exit_code) == false)
	{
		free_shell_data(shell_data);
		ft_exit_str_fd(ERROR_NUMERIC_ARG, STDERR_FILENO);
	}
	else
	{
		exit_code = exit_atoi(exit_code, shell_data);
		free_shell_data(shell_data);
		exit(exit_code);
	}
}

void	ft_exit(char **cmds, t_data *shell_data)
{
	int	return_value;
	
	if (cmds == NULL)
		handle_no_args(shell_data);
	else if (cmds != NULL && cmds[1] != NULL)
		handle_too_many_args(shell_data);
	else if (cmds != NULL && cmds[1] == NULL)
		handle_numeric_arg(cmds[0], shell_data);
}
