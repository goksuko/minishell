#include "../../includes/minishell.h"

// t_env	*init_env_var(void)
// {
// 	printf("----INIT ENV VAR----\n");
// 	t_env	*new_env_var;

// 	new_env_var = (t_env *)malloc(sizeof(t_env));
// 	if (new_env_var == NULL)
// 		return (NULL);
// 	new_env_var->key = NULL;
// 	new_env_var->value = NULL;
// 	new_env_var->next = NULL;
// 	return (new_env_var);
// }

void	execute_shell(t_tree **ast, t_data *shell_data)
{
	printf("----EXECUTE SHELL----\n");
	// t_env	*env_var;
	
	// env_var = init_env_var();
	// if (env_var == NULL)
	// {
	// 	free_tree(ast);
	// 	ft_exit_str_fd(ERROR_ALLOCATION, STDERR_FILENO);
	// }
	// add NULL check but again this is only for testing purposes
	// an initial check to check if the ast has a pipe inside it
	// if it has, do the piping
	// else, execute the command
	if ((*ast)->type == N_COMMAND)
	{
		printf("%s\n", (*ast)->argument[0]);
		if (is_builtin((*ast)->argument[0]) == true)
			execute_builtin(ast, &shell_data->env_list);
		else
			execute_command((*ast)->argument, shell_data);
	}
	// else if ((*ast)->type == N_PIPE)
	// 	execute_pipe(ast, env_var);
}

char	*find_path2(char *identifier, char *path_from_shell_data)
{
	char	*path;
	char	**path_split;
	char	*tmp;
	int		i;

	printf("main_command: %s\n", identifier);
	if (access(identifier, F_OK | X_OK) == 0)
		return (identifier);
	printf("main_command was not accessible\n");
	path_split = ft_split(path_from_shell_data, ':');
	if (errno == ENOMEM || path_split == NULL)
		ft_exit_perror(1, "path_split in find_path");
	i = 0;
	while (path_split[i])
	{
		printf("path_split[%d]: %s\n", i, path_split[i]);
		// if (is_file(path_split[i]))
		// {
		// 	if (info-> infile == NULL)
		// 		info->infile = path_split[i];
		// 	else if (info->outfile != NULL) //check if this is correct
		// 		info->outfile = path_split[i];
		// }
		tmp = ft_strjoin(path_split[i], "/");
		printf("tmp: %s\n", tmp);
		if (errno == ENOMEM || tmp == NULL)
			ft_exit_perror(1, "tmp in find_path");
		path = ft_strjoin(tmp, identifier);
		printf("path: %s\n", path);
		if (errno == ENOMEM || path == NULL)
			ft_exit_perror(1, "path in find_path");
		free(tmp);
		if (access(path, F_OK | X_OK) == 0)
			return (free_matrix(path_split), path);
		free(path);
		i++;
	}
	free_matrix(path_split);
	return (NULL);
}

char	*before_exec2(char *identifier, t_data *shell_data, char **arguments)
{
	char	*path;

	path = NULL;
	if (identifier[0] == ' ')
	{
		ft_exit_str_fd(ERROR_NOT_DIR, STDERR_FILENO);
	}
	if (arguments[0])
		path = find_path2(arguments[0], shell_data->path);
	else
	{
		ft_exit_str_fd(ERROR_PERM, STDERR_FILENO);
	}
	if (!path)
	{
		ft_putstr3_fd("zsh: command not found: ", arguments[0], "\n", STDERR_FILENO);
		exit(127);
	}
	printf("path before exec: %s\n", path);
	return (path);
}

void execute_command(char **arguments, t_data *shell_data)
{
	char *path;

	path = NULL;
	path = before_exec2(arguments[0], shell_data, arguments);
	printf("\npath: %s\n", path);
	if (execve(path, arguments, shell_data->envp) == -1)
	{
		ft_exit_perror(ERROR_EXECVE, "execve in start_exec");
	}
	return ;

}