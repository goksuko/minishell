#include "../../includes/minishell.h"

int	execute_builtin(char **cmds, t_data *shell_data)
{
	printf("----EXECUTE BUILTIN----\n");
	int	return_value;
	int	cmd_len;

	return_value = -1;
	cmd_len = ft_strlen(cmds[0]);
	if (cmd_len == 4 && (ft_strncmp(cmds[0], "echo", 4) == 0 || ft_strncmp(cmds[0], "ECHO", 4) == 0))
		return_value = ft_echo(cmds + 1, shell_data->info);
	else if (cmd_len == 2 && ft_strncmp(cmds[0], "cd", 2) == 0)
		return_value = ft_cd(cmds + 1, shell_data->env_list);
	else if (cmd_len == 3 && (ft_strncmp(cmds[0], "pwd", 3) == 0 || ft_strncmp(cmds[0], "PWD", 3) == 0))
		return_value = ft_pwd(cmds + 1, shell_data);
	if (cmd_len == 6 && ft_strncmp(cmds[0], "export", 6) == 0)
		return_value = ft_export(cmds + 1, shell_data);
	else if (cmd_len == 5 && ft_strncmp(cmds[0], "unset", 5) == 0)
		return_value = ft_unset(cmds + 1, shell_data);
	else if (cmd_len == 3 && (ft_strncmp(cmds[0], "env", 3) == 0 || ft_strncmp(cmds[0], "ENV", 3) == 0))
		return_value = ft_env(cmds + 1, shell_data);
	else if (cmd_len == 4 && ft_strncmp(cmds[0], "exit", 4) == 0)
		ft_exit(cmds + 1, shell_data); // need to check if this works since it does not return anything
	return (return_value);
}

bool	is_builtin(char *command)
{
	printf("------IS BUILTIN CHECK-----\n");
	int	cmd_len;
	
	if (command == NULL)
		return (false);
	cmd_len = ft_strlen(command);
	if (cmd_len == 4 && (ft_strncmp(command, "echo", 4) == 0 || ft_strncmp(command, "ECHO", 4) == 0))
		return (true);
	if (cmd_len == 2 && ft_strncmp(command, "cd", 2) == 0)
		return (true);
	if (cmd_len == 3 && (ft_strncmp(command, "pwd", 3) == 0 || ft_strncmp(command, "PWD", 3) == 0))
		return (true);
	if (cmd_len == 6 && ft_strncmp(command, "export", 6) == 0)
		return (true);
	if (cmd_len == 5 && ft_strncmp(command, "unset", 5) == 0)
		return (true);
	if (cmd_len == 3 && (ft_strncmp(command, "env", 3) == 0 || ft_strncmp(command, "ENV", 3) == 0))
		return (true);
	if (cmd_len == 4 && ft_strncmp(command, "exit", 4) == 0)
		return (true);
	return (false);
}