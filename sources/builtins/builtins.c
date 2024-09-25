#include "../../includes/minishell.h"

bool	is_builtin(char *command)
{
	printf("------IS BUILTIN-----\n");
	if (command == NULL)
		return (false);
	if (ft_strncmp(command, "echo", 5) == 0)
		return (true);
	// if (ft_strncmp(command, "cd", 3) == 0)
	// 	return (true);
	if (ft_strncmp(command, "pwd", 4) == 0)
		return (true);
	// if (ft_strncmp(command, "export", 7) == 0)
	// 	return (true);
	// if (ft_strncmp(command, "unset", 6) == 0)
	// 	return (true);
	// if (ft_strncmp(command, "env", 4) == 0)
	// 	return (true);
	if (ft_strncmp(command, "exit", 5) == 0)
		return (true);
	return (false);
}