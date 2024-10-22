/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 23:08:50 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/22 22:11:47 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	cat_inside(t_token *current)
{
	if (current && ft_strncmp(current->value, "cat", 3) == 0)
		return (true);
	return (false);
}

int	last_exit_code_checks(int exit_code, t_data *data)  // to be checked
{
	if (exit_code == 1 && cat_inside(data->tokens))
		return (0);
	if (WIFSIGNALED(exit_code))
	{
		if (WTERMSIG(exit_code) == 2)
			return (130);
		if (WTERMSIG(exit_code) == 3)
			return (131);
	}
	return (exit_code);
}

// bool child_exit_normal(int *pid, t_data *data)
// {
//     waitpid(*pid, pid, 0);
//     signal(SIGQUIT, child_sigq_handler);
//     data->sigint_child = false;
//     close (pipefd[1]);
//     if (WIFEXITED(*pid) && WEXITSTATUS(*pid) == SIGINT)
//         return (true);
//     return (false);
// }

int clean_from_redir(t_data *data, char **cmd_matrix)
{
	int i;
	int j;
	char **new_cmd_matrix;

	i = 0;
	while (cmd_matrix[i])
	{
		if (ft_strncmp(cmd_matrix[i], "<", 1) == 0 || ft_strncmp(cmd_matrix[i], ">", 1) == 0 || ft_strncmp(cmd_matrix[i], ">>", 2) == 0)
			break;
		i++;
	}
	new_cmd_matrix = ft_calloc(i + 1, sizeof(char *));
	if (errno == ENOMEM || !new_cmd_matrix)
		return (error_assign(data, ERROR_ALLOCATION));
	j = 0;
	while (j < i)
	{
		new_cmd_matrix[j] = ft_strdup(cmd_matrix[j]);
		if (errno == ENOMEM || !new_cmd_matrix[j])
			return (error_assign(data, ERROR_ALLOCATION));
		j++;
	}
	new_cmd_matrix[j] = NULL;
	data->cmd_matrix = new_cmd_matrix;
	printf_array(data->cmd_matrix);
	ft_free_matrix(cmd_matrix);
	return (SUCCESS);
}

int	heredoc_fork(t_data *data)
{
	int		here_doc_fd;
	pid_t	pid;
	int		status;
	char	*path;
	
	handle_signals(HEREDOC);
	here_doc_fd = open("0ur_h3r3_d0c", O_RDONLY, 0777);
	if (here_doc_fd < 0)
		return (error_assign(data, ERROR_FILE_OPEN));
	pid = fork(); // to also signal???
	if (pid < 0)
		return (error_assign(data, ERROR_FORK));
	if (pid == 0)
	{
		if (init_heredoc(data) > 0)
			exit(data->exit_code);
		path = data->path;
		if (path == NULL)
			exit(error_assign(data, ERROR_NULL_PATH));
		if (clean_from_redir(data, data->cmd_matrix) > 0)
			exit(data->exit_code);
		if (data->here_doc_outfile_fd != -10)
		{
			if (dup2(data->here_doc_outfile_fd, STDOUT_FILENO) < 0)
				exit(error_assign(data, ERROR_DUP2));
		}
		if (execve(path, data->cmd_matrix, data->envp) == -1)
			exit(error_assign(data, ERROR_EXECVE));
	}
	else
	{
		waitpid(pid, &status, 0);
		if (unlink("0ur_h3r3_d0c") < 0)
			return (error_assign(data, ERROR_UNLINK));
		// if (WIFEXITED(data->exit_code))
		// 	data->exit_code = WEXITSTATUS(data->exit_code);
		//???? signals
	}
	// if (child_exit_normal(&pid, data))
	return (SUCCESS);	
}

int first_checks(t_data *data)
{
	char	**cmd_matrix;

	cmd_matrix = NULL;
	if (data->cmds[0][0] == ' ')
		return(error_assign(data, ERROR_NOT_DIR));
	cmd_matrix = ft_split(data->cmds[0], ' ');
	if (!cmd_matrix || errno == ENOMEM)
		return (error_assign(data, ERROR_ALLOCATION));
	data->cmd_matrix = cmd_matrix;
	if (cmd_matrix[0])
		data->path = find_path(data->info, cmd_matrix[0]);
	else
		return (error_assign(data, ERROR_PERM));
	if (!data->path)
		return(error_assign(data, ERROR_NOT_DIR));
	return (SUCCESS);
}

int	execute_shell(t_data *data)
{
	data->info->pipe_read_end = STDIN_FILENO;
	update_path(data);
	if (heredoc_inside(data->tokens))
	{
		if (first_checks(data) > 0)
		{
			free_system_error(data, data->exit_code);
			return (data->exit_code);
		}
		if (heredoc_fork(data) > 0)
			return (data->exit_code);
	}
	else
	{
		if (create_children(data) > 0)
			return (data->exit_code);
	}
	// data->exit_code = last_exit_code_checks(data->exit_code, data); // to be checked
	// free_system(data);
	return (SUCCESS);
}

int	is_file(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (false);
	return (S_ISREG(path_stat.st_mode));
}
