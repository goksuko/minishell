/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:36:47 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/07/02 12:23:05 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t	child_process(t_pipex *info, char **argv, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close_pipex(info, NULL);
		ft_exit_perror(ERROR_FORK, "fork in child process");
	}
	if (pid == 0)
	{
		if (info->curr_cmd == 2)
		{
			if (dup2(info->fd_in, STDIN_FILENO) == -1)
				ft_exit_perror(ERROR_DUP2, "dup2 for infile in child process");
			close_safe(info->fd_in, NULL);
		}
		if (dup2(info->pipefd[1], STDOUT_FILENO) == -1)
			ft_exit_perror(ERROR_DUP2, "dup2 for pipefd in child process");
		close_safe(info->pipefd[1], NULL);
		start_exec(info, argv, envp);
	}
	return (pid);
}

pid_t	last_child_process(t_pipex *info, char **argv, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_exit_perror(ERROR_FORK, "fork in last child process");
	if (pid == 0)
	{
		if (dup2(info->pipefd[0], STDIN_FILENO) == -1)
			ft_exit_perror(ERROR_DUP2, "dup2 for pipefd in last child process");
		close_safe(info->pipefd[0], info);
		if (dup2(info->fd_out, STDOUT_FILENO) == -1)
			ft_exit_perror(ERROR_DUP2, "dup2 for outfile in last child process");
		close_safe(info->fd_out, info);
		start_exec(info, argv, envp);
	}
	return (pid);
}

int	create_children(t_pipex *info, char *argv[], char **envp)
{
	int		i;
	pid_t	pid;
	pid_t	pid_last;
	int		status;

	i = 1;
	while (i < info->nbr_of_cmds)
	{
		if (pipe(info->pipefd) == -1)
			ft_close_exit_perror(info, NULL, ERROR_PIPE, "pipe in create children");
		pid = child_process(info, argv, envp);
		close_safe(info->pipefd[1], info);
		dup2_safe(info->pipefd[0], STDIN_FILENO, info);
		info->curr_cmd++;
		i++;
	}
	pid_last = last_child_process(info, argv, envp);
	while (waitpid(pid, &status, 0) != -1)
		;
	waitpid(pid_last, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

void	initialize_info(t_pipex *info, char *argv[], int argc)
{
	info->fd_in = open(argv[1], O_RDONLY, 0777);
	if (info->fd_in < 0)
	{
		free(info);
		ft_exit_perror(ERROR_FILE_OPEN, "infile in initialize");
	}
	info->fd_out = open(argv[argc - 1], O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (info->fd_out < 0)
	{
		close(info->fd_in);
		free(info);
		ft_exit_perror(ERROR_FILE_OPEN, "outfile in initialize");
	}
	info->nbr_of_cmds = argc - 3;
	info->curr_cmd = 2;
}

int	pipex(int argc, char *argv[], char **envp)
{
	int		path_no;
	t_pipex	*info;
	int		exit_code;

	ft_printf("pipex\n");
	if (argc < 5)
		return (ft_print_error(ERROR_ARGUMENT_COUNT));
	info = (t_pipex *)ft_calloc(1, sizeof(t_pipex));
	if (info == NULL || errno == ENOMEM)
		ft_exit_perror(ERROR_ALLOCATION, "info in main");
	initialize_info(info, argv, argc);
	path_no = find_path_index(envp);
	if (envp[path_no] == NULL)
		return (ft_print_error(ERROR_NULL_PATH));
	if (path_no == 0)
		return (command_not_found(argv));
	exit_code = create_children(info, argv, envp);
	free(info);
	return (exit_code);
}
