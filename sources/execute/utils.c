// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   utils.c                                            :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2024/05/16 13:34:42 by akaya-oz      #+#    #+#                 */
// /*   Updated: 2024/09/06 16:19:04 by akaya-oz      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../includes/minishell.h"

void	*free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return (NULL);
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	if (matrix)
	{
		free(matrix);
		matrix = NULL;
	}
	return (NULL);
}

void	close_pipex(t_pipex *info, char **matrix)
{
	// printf("close_pipex\n");
	close(info->fd_in);
	close(info->fd_out);
	close(info->pipefd[0]);
	close(info->pipefd[1]);
	free(info);
	if (matrix)
		free_matrix(matrix);
}

char	*before_exec(char *long_command, t_pipex *info, char **cmd_matrix)
{
	char	*path;

	printf("---before_exec---\n");
	path = NULL;
	if (long_command[0] == ' ')
	{
		close_pipex(info, cmd_matrix);
		ft_exit_str_fd(ERROR_NOT_DIR, STDERR_FILENO);
	}
	if (cmd_matrix[0])
		path = find_path(info, cmd_matrix[0], info->path_from_getenv);
	else
	{
		close_pipex(info, cmd_matrix);
		ft_exit_str_fd(ERROR_PERM, STDERR_FILENO);
	}
	if (!path)
	{
		ft_putstr3_fd("zsh: command not found: ", cmd_matrix[0], "\n", STDERR_FILENO);
		close_pipex(info, cmd_matrix);
		exit(127);
	}
	printf("path before exec: %s\n", path);
	return (path);
}

// start_exec(info, info->cmds, info->data->envp);
void	start_exec(t_pipex *info)
{
	char	**cmd_matrix;
	char	*path;
	// char	*line;
	// char	*long_command;
	// char	*long_corrected_command;

	printf("---start_exec---\n");

	// if (info->data->ast->type == N_COMMAND)
	// {
	// 	printf("%s\n", info->data->ast->argument[0]);
	// 	if (is_builtin(info->data->ast->argument[0]) == true)
	// 		execute_builtin(info->data);
	// 	else
	// 		execute_command(info->data);
	// }


	path = NULL;
	// printf("curr_cmd: %d\n", info->curr_cmd);
	// if (info->special_command == NULL)
	// 	long_command = info->cmds[info->curr_cmd - 1];
	// else
	// {
	// 	long_command = info->special_command;
	// 	info->special_command = NULL;
	// }	
	// printf("long_command: %s\n", long_command);
	// long_corrected_command = clean_redirects(long_command);
	// printf("long_corrected_command: %s\n", long_corrected_command);
	// cmd_matrix = ft_split(long_corrected_command, ' ');
	cmd_matrix = ft_split(info->cmds[info->curr_cmd - 1], ' ');
	// printf_array(cmd_matrix);
	if (!cmd_matrix || errno == ENOMEM)
		ft_exit_perror(ERROR_ALLOCATION, "cmd_matrix in start_exec");
	// path = before_exec(long_corrected_command, info, cmd_matrix);
	path = before_exec(info->cmds[info->curr_cmd - 1], info, cmd_matrix);
	// printf("\npath: %s\n", path);
	// if (builtin)
	// {
	// 	// execute_builtin(info->data);
	// -1 for not execured, > 0 for exit code
	//  0 executed with success
	// }
	// else
	// {
	printf("Test\n");
	// printf("cmd matrix:\n");
	// printf_array(cmd_matrix);
	// char *line;
	// while (info->limiter)
	// {
	// 	line = readline("minishell of 🦸 Goksu & 🧚 Vanessa > ");
	// 	// printf("line: --%s--\n", line);
	// 	write(STDOUT_FILENO, line, strlen(line)); // these two lines should stay!!
	// 	write(STDOUT_FILENO, "\n", 1);
	// 	if ((ft_strlen(line) == ft_strlen(info->limiter)) && (ft_strncmp(line, info->limiter, ft_strlen(info->limiter)) == 0))
	// 	{
	// 		// printf("limiter found\n");
	// 		write(STDOUT_FILENO, "test\n", 5);
	// 		unlink("our_here_doc");
	// 		break;
	// 	}
	// }
	if (info->limiter)
		printf("limiter: %s\n", info->limiter);
	else
	{
		if (info->curr_cmd == 1)
		{	
			printf("test1\n");
			if (execve(path, cmd_matrix, info->data->envp) == -1)
			{
				close_pipex(info, cmd_matrix);
				printf("test2	\n");
				ft_exit_perror(ERROR_EXECVE, "execve in start_exec");
			}
		}
	}
	return ;
}

char	*put_main_command(char *command, char space)
{
	char	*temp;
	int		i;

	i = 0;
	while (command[i] != space && command[i] != '\0')
		i++;
	temp = (char *)ft_calloc(sizeof(char), (i + 1));
	if (!temp || errno == ENOMEM)
		ft_exit_perror(ERROR_ALLOCATION, "temp in put_main_command");
	i = 0;
	while (command[i] != space && command[i] != '\0')
	{
		temp[i] = command[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}


bool	is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	return (false);
}
