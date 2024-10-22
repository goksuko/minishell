/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 23:08:50 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/22 14:53:38 by akaya-oz      ########   odam.nl         */
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

int	heredoc_fork(t_data *data)
{
	int		here_doc_fd;
	pid_t	pid;
	int		status;

	handle_signals(HEREDOC);
	printf("before open\n");
	here_doc_fd = open("0ur_h3r3_d0c", O_RDONLY, 0777);
	if (here_doc_fd < 0)
		return (error_assign(data, ERROR_FILE_OPEN));
	pid = fork(); // to also signal???
	if (pid < 0)
		return (error_assign(data, ERROR_FORK));
	if (pid == 0)
	{
		if (init_heredoc(data) > 0)
			return (data->exit_code);
		char	**cmd_matrix;
		char	*path;

		path = NULL;
		cmd_matrix = ft_split(data->cmds[0], ' ');
		if (!cmd_matrix || errno == ENOMEM)
			return (false);
		update_path(data);
		path = before_exec(data->cmds[0], info, cmd_matrix);
		if (path == NULL)
		{
			ft_free_matrix(cmd_matrix);
			return (true);
		}
		if (execve(path, cmd_matrix, info->data->envp) == -1)
			return (false);
		return (true);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		// if (WIFEXITED(data->exit_code))
		// 	data->exit_code = WEXITSTATUS(data->exit_code);
		//???? signals
	}
	// if (child_exit_normal(&pid, data))
	return (SUCCESS);	
}


bool	execute_shell(t_data *data)
{
	int	exit_code;

	printf("inside execute_shell\n");
	// data->nbr_of_pipes = find_pipe_count(data->tokens);
	// data->exit_code = 0;
	data->info->pipe_read_end = STDIN_FILENO;
	// printf("%d\n", data->nbr_of_pipes);
	if (heredoc_inside(data->tokens))
	{
		printf("inside loop\n");
		heredoc_fork(data);	
	}
	else
	{
		if (create_children(data) > 0)
		{
			return (false);
		}
	}
	if (data->info->limiter)
	{
		if (unlink("0ur_h3r3_d0c") < 0)
			return (false);
	}
	exit_code = data->exit_code;
	data->exit_code = last_exit_code_checks(exit_code, data); // to be checked
	// free_system(data);
	return (true);
}

int	is_file(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (false);
	return (S_ISREG(path_stat.st_mode));
}
