#include "../../includes/minishell.h"

// include tilde check for cd and export and unset

int	execute_builtin(char **cmds, t_data *shell_data)
{
	printf("----EXECUTE BUILTIN----\n");
	int	return_value;
	int	cmd_len;

	return_value = -1;
	cmd_len = ft_strlen(cmds[0]);
	if (cmd_len == 4 && ft_strncmp(cmds[0], "echo", 4) == 0)
		return_value = ft_echo(cmds + 1, shell_data->info);
	if (cmd_len == 2 && ft_strncmp(cmds[0], "cd", 2) == 0)
		return_value = ft_cd(cmds + 1, shell_data->info, shell_data->env_list);
	if (cmd_len == 3 && ft_strncmp(cmds[0], "pwd", 3) == 0)
		return_value = ft_pwd(cmds + 1, shell_data->info);
	if (cmd_len == 6 && ft_strncmp(cmds[0], "export", 6) == 0)
		return_value = ft_export(cmds + 1);
	// if (ft_strncmp(arguments[0], "unset", 6) == 0)
	// 	return (ft_unset(arguments));
	// if (ft_strncmp(arguments[0], "env", 4) == 0)
	// 	return (ft_env(env_var));
	if (cmd_len == 4 && ft_strncmp(cmds[0], "exit", 4) == 0)
		ft_exit(cmds + 1, shell_data);
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