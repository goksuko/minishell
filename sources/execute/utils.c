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

// void	*free_matrix(char **matrix)
// {
// 	int	i;

// 	i = 0;
// 	if (matrix == NULL)
// 		return (NULL);
// 	while (matrix[i])
// 	{
// 		free(matrix[i]);
// 		matrix[i] = NULL;
// 		i++;
// 	}
// 	if (matrix)
// 	{
// 		free(matrix);
// 		matrix = NULL;
// 	}
// 	return (NULL);
// }

// void	close_info(t_info *info)
// {
// 	// printf("close_info\n");
// 	close(info->fd_in);
// 	close(info->fd_out);
// 	close(info->pipefd[0]);
// 	close(info->pipefd[1]);
// 	free(info);
// }

char	*before_exec(char *long_command, t_info *info, char **cmd_matrix)
{
	char	*path;

	// printf("---before_exec---\n");
	path = NULL;
	if (long_command[0] == ' ')
	{
		// close_info(info);
		// ft_exit_str_fd(ERROR_NOT_DIR, STDERR_FILENO);
		ft_exit_data_error(info->data, ERROR_NOT_DIR);
	}
	if (cmd_matrix[0])
		// path = find_path(info, cmd_matrix[0], info->path_from_getenv);
		path = find_path(info, cmd_matrix[0]);
	else  /////////////////////////////////////////////////////////////////// CHECK HERE
	{
		ft_printf_fd(STDERR_FILENO, "bash: %s: Permission denied\n", info->outfile);
		info->data->exit_code = 126;
		free_data(&info->data); //free_system
		// exit(126);
	}
	if (!path)
	{
		ft_putstr3_fd("command not found: ", cmd_matrix[0], "\n", STDERR_FILENO);
		free_data(&info->data); //free_system
		info->data->exit_code = 127;
		// exit(127);
	}
	printf("path before exec: %s\n", path);
	return (path);
}


pid_t	heredoc_child_process(t_info *info, char **cmd_matrix, char *path)
{
	pid_t	pid;
	int		here_doc_fd;
	(void)path;

	here_doc_fd = here_doc_fd_check(info->data);
	printf("--heredoc_child_process--\n");
	pid = fork();
	if (pid == -1)
	{
		close_info(info);
		ft_exit_perror(ERROR_FORK, "fork in child process");
	}
	else if (pid == 0)
	{
		printf("limiter: %s\n", info->limiter);
		printf("fd_in: %d\n", info->fd_in);
		printf("here_doc_fd: %d\n", here_doc_fd);
		printf("fd_out: %d\n", info->fd_out);
		// close_safe(info->fd_in, info);
		dup2_safe(info->fd_in, here_doc_fd, info);
		printf("fd_in: %d\n", info->fd_in);
		printf("here_doc_fd: %d\n", here_doc_fd);
		printf("fd_out: %d\n", info->fd_out);
		info->fd_out = STDOUT_FILENO;
		// dup2_safe(STDOUT_FILENO, info->fd_out, info);
		printf("fd_out: %d\n", info->fd_out);
		printf("now writing to STDOUT\n");
	}
	else
	{
		// update_path(info->data);
		if (execve(path, cmd_matrix, info->data->envp) == -1)
		// if (execve(info->data->path, cmd_matrix, info->data->envp) == -1)
		{
			ft_exit_data_perror(info->data, ERROR_EXECVE, "execve in heredoc start_exec");
		}
	}
	return (pid);
}


void	start_exec(t_info *info)
{
	char	**cmd_matrix;
	char	*path;
	// pid_t	pid;
	// int		status;

	// printf("---start_exec---\n");
	path = NULL;
	// printf("cmds::::::::::::::::::::::\n");
	// printf_array(info->data->info->cmds);
	// printf("curr_cmd: %s\n", info->cmds[info->curr_cmd - 1]);
	cmd_matrix = ft_split(info->data->cmds[info->curr_cmd], ' ');
	if (!cmd_matrix || errno == ENOMEM)
		ft_exit_data_perror(info->data, ERROR_ALLOCATION, "cmd_matrix in start_exec");
	// printf("cmd_matrix::::::::::::::::::::::\n");
	// printf_array(cmd_matrix);
	update_path(info->data);
	path = before_exec(info->data->cmds[info->curr_cmd], info, cmd_matrix);
	// if (info->limiter)
	// {
	// 	printf("test_me\n");
	// 	pid = heredoc_child_process(info, cmd_matrix, path);
		// printf("limiter: %s\n", info->limiter);
		// dup2_safe(STDOUT_FILENO, info->fd_out, info);
		// printf("fd_out: %d\n", info->fd_out);
		// printf("now writing to STDOUT\n");
		// if (execve(path, cmd_matrix, info->data->envp) == -1)
		// {
		// 	close_info(info, cmd_matrix);
		// 	printf("test3	\n");
		// 	ft_exit_perror(ERROR_EXECVE, "execve in start_exec");
		// }
		// unlink("0ur_h3r3_d0c");
	// }
	// else
	// {
		// if (info->curr_cmd == 1) // with this pipes stopped working right, so commented out
		// {	
	// update_path(info->data);
	if (execve(path, cmd_matrix, info->data->envp) == -1)
	// if (execve(info->data->path, cmd_matrix, info->data->envp) == -1)
	{		
		ft_exit_data_perror(info->data, ERROR_EXECVE, "execve in start_exec");
	}
		// }
	// }
	// waitpid(pid, &status, 0);
	// waitpid(-1, &status, 0);
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
