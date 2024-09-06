#include "../../includes/minishell.h"

int	execute_builtin(t_data *shell_data)
{
	printf("----EXECUTE BUILTIN----\n");
	t_env **env_var;
	t_tree **ast;

	ast = &shell_data->ast;
	env_var = &shell_data->env_list;	
	if (ft_strncmp((*ast)->argument[0], "echo", 5) == 0)
		return (ft_echo((*ast)->argument));
	// if (ft_strncmp(arguments[0], "cd", 3) == 0)
	// 	return (ft_cd(arguments));
	if (ft_strncmp((*ast)->argument[0], "pwd", 4) == 0)
		return (ft_pwd());
	// if (ft_strncmp(arguments[0], "export", 7) == 0)
	// 	return (ft_export(arguments));
	// if (ft_strncmp(arguments[0], "unset", 6) == 0)
	// 	return (ft_unset(arguments));
	// if (ft_strncmp(arguments[0], "env", 4) == 0)
	// 	return (ft_env(env_var));
	if (ft_strncmp((*ast)->argument[0], "exit", 5) == 0)
		ft_exit(ast, env_var);
	return (1);
}

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