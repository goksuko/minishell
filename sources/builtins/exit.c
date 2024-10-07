#include "../../includes/minishell.h"

void	handle_numeric_arg(char *exit_code, t_data *shell_data)
{
	int	exit_code_value;

	if (arg_is_digit(exit_code) == false)
	{
		free_shell_data(&shell_data);
		ft_exit_str_fd(ERROR_NUMERIC_ARG, STDERR_FILENO);
	}
	else
	{
		exit_code_value = exit_atoi(exit_code, shell_data);
		//free_shell_data(&shell_data); // commented out for testing purposes because free_shell_data causes a seg fault currently
		exit(exit_code_value); //check again if this is really correct...although it should
	}
}

void	ft_exit(char **cmds, t_data *shell_data)
{	
	if (cmds[0] == NULL)
	{
		free_shell_data(&shell_data);
		exit(SUCCESS);
	}
	else if (cmds != NULL && cmds[1] != NULL)
	{
		free_shell_data(&shell_data);
		ft_exit_str_fd(ERROR_TOO_MANY_ARGS, STDERR_FILENO);
	}	
	else if (cmds != NULL && cmds[1] == NULL)
		handle_numeric_arg(cmds[0], shell_data);
}
