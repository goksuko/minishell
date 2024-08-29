#include "../../includes/minishell.h"

int	builtins(char **arguments)
{
	if (ft_strncmp(arguments[0], "echo", 5) == 0)
		return (ft_echo());
	if (ft_strncmp(arguments[0], "cd", 3) == 0)
		return (ft_cd());
	if (ft_strncmp(arguments[0], "pwd", 4) == 0)
		return (ft_pwd());
	if (ft_strncmp(arguments[0], "export", 7) == 0)
		return (ft_export());
	if (ft_strncmp(arguments[0], "unset", 6) == 0)
		return (ft_unset());
	if (ft_strncmp(arguments[0], "env", 4) == 0)
		return (ft_env());
	if (ft_strncmp(arguments[0], "exit", 5) == 0)
		return (ft_exit());
}

bool	is_builtin(char *command)
{
	if (command == NULL)
		return (false);
	if (ft_strncmp(command, "echo", 5) == 0)
		return (true);
	if (ft_strncmp(command, "cd", 3) == 0)
		return (true);
	if (ft_strncmp(command, "pwd", 4) == 0)
		return (true);
	if (ft_strncmp(command, "export", 7) == 0)
		return (true);
	if (ft_strncmp(command, "unset", 6) == 0)
		return (true);
	if (ft_strncmp(command, "env", 4) == 0)
		return (true);
	if (ft_strncmp(command, "exit", 5) == 0)
		return (true);
	return (false);
}