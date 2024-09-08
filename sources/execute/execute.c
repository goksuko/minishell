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

int find_child_nbr(t_tree *ast)
{
	int	nbr_of_chldrn;
	int	i;

	i = 0;
	if (ast->type == N_PIPE)
		return (1);
	else
	{
		nbr_of_chldrn = 1;
		while (ast->token_types[i] != NULL)
		{
			if (ast->token_types[i] == token_type_to_string(T_SMALLER) || \
				ast->token_types[i] == token_type_to_string(T_GREATER) || \
				ast->token_types[i] == token_type_to_string(T_DSMALLER) || \
				ast->token_types[i] == token_type_to_string(T_DGREATER))
				nbr_of_chldrn++;
			i++;
		}
		return (nbr_of_chldrn);
	}
}

// void	initialize_info(t_pipex *info, t_data *shell_data)
// {
// 	ft_printf("\ninitialize_info\n");
// 	info->path = shell_data->path;
// 	find_infile(info);
// 	find_outfile(info);
// 	info->data = shell_data;
// 	info->curr_cmd = 1;
// 	info->pipefd[0] = 0;
// 	info->pipefd[1] = 0;
// 	return ;
// }

void	execute_node(t_tree *ast, t_data *shell_data)
{
	printf("----EXECUTE NODE----\n");
	int nbr_of_chldrn;
	t_pipex	*info;
	int		exit_code;

	nbr_of_chldrn = find_child_nbr(ast);
	printf("nbr_of_chldrn: %d\n", nbr_of_chldrn);
	info = (t_pipex *)ft_calloc(1, sizeof(t_pipex));
	if (info == NULL || errno == ENOMEM)
		ft_exit_perror(ERROR_ALLOCATION, "info in pipex");
	shell_data->info = info;
	info->nbr_of_cmds = nbr_of_chldrn;
	shell_data->nbr_of_cmds = info->nbr_of_cmds;
	printf("nbr_of_cmds: %d\n", info->nbr_of_cmds);
	shell_data->cmds = shell_data->ast->argument;
	info->cmds = shell_data->cmds;
	initialize_info(info, shell_data);
	// printf("infile: %s\n", info->infile);
	// printf("outfile: %s\n", info->outfile);
	printf("initilaization is done\n\n*******\n\n");
	exit_code = create_children(shell_data);
	printf("exit_code: %d\n", exit_code);
	shell_data->exit_code = exit_code;
}

int		find_pipe_count(t_token *tokens)
{
	int	pipe_count;

	pipe_count = 0;
	while (tokens->next != NULL)
	{
		if (tokens->type == T_PIPE)
			pipe_count++;
		tokens = tokens->next;
	}
	return (pipe_count);
}


void	execute_shell(t_data *shell_data)
{
	printf("----EXECUTE SHELL----\n");
	// t_env	*env_var;
	// t_tree *ast;

	// ast = shell_data->ast;
	shell_data->exit_code = 0;
	shell_data->nbr_of_pipes = find_pipe_count(shell_data->tokens);
	printf("nbr_of_pipes: %d\n", shell_data->nbr_of_pipes);
	// while(ast->right != NULL)
	// {
	// 	if (ast->type == N_PIPE)
	// 		execute_pipe(ast, shell_data);
	// 	else
	// 		execute_node(ast, shell_data);
	// 	ast = ast->right;
	// }

	if (shell_data->nbr_of_pipes == 0)
		execute_node(shell_data->ast, shell_data);
	else
		shell_data->exit_code = pipex(shell_data);
	
		

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

	// if (ast->type == N_COMMAND)
	// {
	// 	printf("%s\n", ast->argument[0]);
	// 	if (is_builtin(ast->argument[0]) == true)
	// 		execute_builtin(shell_data);
	// 	else
	// 		execute_command(shell_data);
	// }

	// else if ((*ast)->type == N_PIPE)
	// 	execute_pipe(ast, shell_data);
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

void execute_command(t_data *shell_data)
{
	char *path;
	char **arguments;

	printf("----EXECUTE COMMAND----\n");
	path = NULL;
	arguments = shell_data->ast->argument;
	path = before_exec2(arguments[0], shell_data, arguments);
	printf("\npath: %s\n", path);
	if (execve(path, arguments, shell_data->envp) == -1)
	{
		ft_exit_perror(ERROR_EXECVE, "execve in execute_command");
	}
	return ;

}

// void execute_pipe(t_tree **ast, t_data *shell_data)
// {
// 	t_pipex	*info;
// 	int		exit_code;
// 	int		pipe_count;

// 	ft_printf("---EXECUTE PIPE---\n");
// 	info = (t_pipex *)ft_calloc(1, sizeof(t_pipex));
// 	if (info == NULL || errno == ENOMEM)
// 		ft_exit_data_perror(shell_data, ERROR_ALLOCATION, "info in pipex");
// 	shell_data->info = info;
// 	pipe_count = check_pipe_count(ast);
// 	info->nbr_of_cmds = pipe_count + 1;
// 	printf("nbr_of_cmds: %d\n", info->nbr_of_cmds);
// 	initialize_cmds(data, info);
// 	initialize_info(info, data);
// 	// printf("infile: %s\n", info->infile);
// 	// printf("outfile: %s\n", info->outfile);
// 	printf("initilaization is done\n\n*******\n\n");
// 	exit_code = create_children(data);
// 	printf("exit_code: %d\n", exit_code);
// 	free_system(data);
// 	return (exit_code);
// }

// int check_pipe_count(t_tree **ast)
// {
// 	int	pipe_count;

// 	pipe_count = 0;
// 	while ((*ast)->type == N_PIPE)
// 	{
// 		pipe_count++;
// 		*ast = (*ast)->left;
// 	}
// 	return (pipe_count);
// }