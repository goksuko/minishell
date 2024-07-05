/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:36:47 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/07/05 23:01:48 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t	child_process(t_pipex *info)
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
		if (info->curr_cmd == 1)
		{
			if (dup2(info->fd_in, STDIN_FILENO) == -1)
				ft_exit_perror(ERROR_DUP2, "dup2 for infile in child process");
			close_safe(info->fd_in, NULL);
		}
		if (dup2(info->pipefd[1], STDOUT_FILENO) == -1)
			ft_exit_perror(ERROR_DUP2, "dup2 for pipefd in child process");
		close_safe(info->pipefd[1], NULL);
		start_exec(info, info->cmds, info->data->envp);
	}
	return (pid);
}

pid_t	last_child_process(t_pipex *info)
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
			ft_exit_perror(ERROR_DUP2, "dup2 for outfile in last child");
		close_safe(info->fd_out, info);
		start_exec(info, info->cmds, info->data->envp);
	}
	return (pid);
}

int	create_children(t_data *data)
{
	int		i;
	pid_t	pid;
	pid_t	pid_last;
	int		status;

	i = 0;
	while (i < data->nbr_of_cmds)
	{
		if (pipe(data->info->pipefd) == -1)
			ft_close_exit_perror(data->info, NULL, ERROR_PIPE,
				"pipe in create children");
		pid = child_process(data->info);
		close_safe(data->info->pipefd[1], data->info);
		dup2_safe(data->info->pipefd[0], STDIN_FILENO, data->info);
		data->info->curr_cmd++;
		i++;
	}
	pid_last = last_child_process(data->info);
	while (waitpid(pid, &status, 0) != -1)
		;
	waitpid(pid_last, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (SUCCESS);
}

void	initialize_cmds(t_data *data, t_pipex *info)
{
	char	**cmds;

	ft_printf("initialize_cmds\n");
	cmds = ft_split(data->line, '|');
	if (cmds == NULL || errno == ENOMEM)
		ft_exit_data_perror(data, ERROR_ALLOCATION, "cmds in initialize");
	data->cmds = cmds;
	info->cmds = cmds;
	data->nbr_of_cmds = ft_strlen(*cmds);
	info->nbr_of_cmds = data->nbr_of_cmds;
	return ;
}

char	*find_infile(t_pipex *info)
{
	char	*infile;

	ft_printf("find_infile\n");
	infile = find_path(info->cmds[0], info->data->envp);
	if (infile == NULL)
	{
		close_pipex(info, NULL);
		ft_exit_data_error(info->data, ERROR_CMD_NOT_FOUND);
	}
	return (infile);
}

char	*find_outfile(t_pipex *info)
{
	char	*outfile;

	ft_printf("find_outfile\n");
	outfile = find_path(info->cmds[info->nbr_of_cmds - 1], info->data->envp);
	if (outfile == NULL)
	{
		close_pipex(info, NULL);
		ft_exit_data_error(info->data, ERROR_CMD_NOT_FOUND);
	}
	return (outfile);
}

void	initialize_info(t_pipex *info, t_data *data)
{
	ft_printf("initialize_info\n");
	info->infile = find_infile(info);
	info->outfile = find_outfile(info);
	info->fd_in = open(info->infile, O_RDONLY);
	if (info->fd_in == -1)
	{
		close_pipex(info, NULL);
		ft_exit_data_perror(data, ERROR_FILE_OPEN, "infile in initialize_info");
	}
	info->fd_out = open(info->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (info->fd_out == -1)
	{
		close_pipex(info, NULL);
		ft_exit_data_perror(data, ERROR_FILE_OPEN,
			"outfile in initialize_info");
	}
	info->data = data;
	info->curr_cmd = 1;
	return ;
}

void	make_path_checks(t_data *data)
{
	int	path_no;

	ft_printf("make_path_checks\n");
	path_no = find_path_index(data->envp);
	if (data->envp[path_no] == NULL)
	{
		free_system(data);
		ft_print_error(ERROR_NULL_PATH);
		exit(ERROR_NULL_PATH);
	}
	if (path_no == 0)
	{
		free_system(data);
		ft_print_error(ERROR_CMD_NOT_FOUND);
		exit(ERROR_CMD_NOT_FOUND);
	}
	return ;
}

int	pipex(t_data *data)
{
	t_pipex	*info;
	int		exit_code;
	int		pipe_count;

	ft_printf("pipex\n");
	pipe_count = check_pipe(data->line);
	info = (t_pipex *)ft_calloc(1, sizeof(t_pipex));
	if (info == NULL || errno == ENOMEM)
		ft_exit_data_perror(data, ERROR_ALLOCATION, "info in pipex");
	info->nbr_of_cmds = pipe_count + 1;
	initialize_cmds(data, info);
	make_path_checks(data);
	initialize_info(info, data);
	exit_code = create_children(data);
	free_system(data);
	return (exit_code);
}
