/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:36:47 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/07/19 00:06:45 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_file(const char *path)
{
    struct stat path_stat;
    if (stat(path, &path_stat) != 0)
        return (false);
    return (S_ISREG(path_stat.st_mode));
}

pid_t	child_process(t_pipex *info)
{
	pid_t	pid;

	printf("child_process\n");
	pid = fork();
	if (pid == -1)
	{
		close_pipex(info, NULL);
		ft_exit_perror(ERROR_FORK, "fork in child process");
	}
	if (pid == 0)
	{
		printf("curr_cmd: %d\n", info->curr_cmd);
		printf("pipefd[0]: %d\n", info->pipefd[0]);
		printf("pipefd[1]: %d\n", info->pipefd[1]);
		if (info->curr_cmd == 1 && info->infile != NULL)
		{
			printf("first command**\n");
			dup2_safe(info->fd_in, STDIN_FILENO, info); // it was fd_in before actually
			close_safe(info->fd_in, info);
		}
		close_safe(info->pipefd[0], info);
		// dup2_safe(info->pipefd[1], STDOUT_FILENO, info);
		close_safe(info->pipefd[1], info);
		printf("ready to start exec\n");
		start_exec(info, info->cmds);
	}
	return (pid);
}

pid_t	last_child_process(t_pipex *info)
{
	pid_t	pid;

	printf("\nlast_child_process\n");
	pid = fork();
	if (pid == -1)
		ft_exit_perror(ERROR_FORK, "fork in last child process");
	if (pid == 0)
	{
		printf("pipefd[0]: %d\n", info->pipefd[0]);
		printf("pipefd[1]: %d\n", info->pipefd[1]);
		printf("fd_in: %d\n", info->fd_in);
		printf("fd_out: %d\n", info->fd_out);
		// close_safe(info->pipefd[1], info);
		// dup2_safe(info->pipefd[0], STDIN_FILENO, info);
		// close_safe(info->pipefd[0], info);
		if (info->outfile != NULL)
		{
			dup2_safe(info->fd_out, STDOUT_FILENO, info);
			close_safe(info->fd_out, info);
		}
		// dup2_safe(info->fd_out, STDOUT_FILENO, info);
		// close_safe(info->fd_out, info);
		// close_safe(info->pipefd[1], info);
		// close_safe(info->pipefd[0], info);
		printf("ready to start last exec\n");
		start_exec(info, info->cmds);
	}
	return (pid);
}

int	create_children(t_data *data)
{
	int		i;
	pid_t	pid;
	pid_t	pid_last;
	int		status;

	printf("create_children\n");
	i = 1;
	printf("nbr_of_cmds: %d\n\n", data->nbr_of_cmds);
	while (i < data->nbr_of_cmds - 1)
	{
		printf("\nin while loop i: %d\n", i);
		if (pipe(data->info->pipefd) == -1)
			ft_close_exit_perror(data->info, NULL, ERROR_PIPE, "pipe in create children");
		pid = child_process(data->info);
		close_safe(data->info->pipefd[1], data->info);
		// dup2_safe(data->info->pipefd[0], STDIN_FILENO, data->info);
		close_safe(data->info->pipefd[0], data->info);
		data->info->curr_cmd++;
		i++;
		printf("sleeping after child (%d)\n", i);
		sleep(1);
	}
	printf("\nsleeping before last child\n");
	sleep(1);
	pid_last = last_child_process(data->info);
	while (waitpid(pid, &status, 0) != -1);
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
	data->nbr_of_cmds = info->nbr_of_cmds;
	return ;
}

char	*find_infile(t_pipex *info)
{
	int		i;
	char	**cmd_split;
	

	ft_printf("\nfind_infile\n");
	i = 0;
	cmd_split = ft_split(info->cmds[0], ' ');
	if (cmd_split == NULL || errno == ENOMEM)
		ft_exit_data_perror(info->data, ERROR_ALLOCATION, "cmd_split in find_infile");
	while (cmd_split[i] != NULL)
	{
		printf("cmd_split[%d]: %s\n", i, cmd_split[i]);
		if (is_file(cmd_split[i]))
		{
			printf("is a file: cmd_split[%d]: %s\n", i, cmd_split[i]);
			ft_strlcpy(info->infile, cmd_split[i], ft_strlen(cmd_split[i]) + 1);
			info->fd_in = open(cmd_split[i], O_RDONLY, 0777);
			printf("info->fd_in: %d\n", info->fd_in);
			if (info->fd_in == -1)
			{
				close_pipex(info, NULL);
				ft_exit_data_perror(info->data, ERROR_FILE_OPEN, "infile in find_infile");
			}
			free_matrix(cmd_split);
			return (cmd_split[i]);
		}
		i++;
	}
	free_matrix(cmd_split);
	info->infile = NULL;
	info->fd_in = STDIN_FILENO; //no need probably
	return (NULL);
}

char	*find_outfile(t_pipex *info) // if file does not exist, should be worked on
{
	int		i;
	char	**cmd_split;
	

	ft_printf("\nfind_outfile\n");
	i = 0;
	cmd_split = ft_split(info->cmds[info->nbr_of_cmds - 1], ' ');
	if (cmd_split == NULL || errno == ENOMEM)
		ft_exit_data_perror(info->data, ERROR_ALLOCATION, "cmd_split in find_outfile");
	while (cmd_split[i] != NULL)
	{
		printf("cmd_split[%d]: %s\n", i, cmd_split[i]);
		if (is_file(cmd_split[i]))
		{
			printf("is a file: cmd_split[%d]: %s\n", i, cmd_split[i]);
			ft_strlcpy(info->outfile, cmd_split[i], ft_strlen(cmd_split[i]) + 1);
			info->fd_out = open(cmd_split[i], O_CREAT | O_TRUNC | O_WRONLY, 0777);
			printf("info->fd_out: %d\n", info->fd_out);
			if (info->fd_out == -1)
			{
				close_pipex(info, NULL);
				ft_exit_data_perror(info->data, ERROR_FILE_OPEN, "outfile in find_outfile");
			}
			free_matrix(cmd_split);
			return (cmd_split[i]);
		}
		i++;
	}
	free_matrix(cmd_split);
	info->outfile = NULL;
	info->fd_out = STDOUT_FILENO; //no need probably
	return (NULL);
}

void	initialize_info(t_pipex *info, t_data *data)
{
	ft_printf("\ninitialize_info\n");
	info->path_from_getenv = getenv("PATH");
	if (info->path_from_getenv == NULL)
	{
		close_pipex(info, NULL);
		ft_exit_data_error(data, ERROR_NULL_PATH);
	}
	printf("path_from_getenv: %s\n", info->path_from_getenv);
	find_infile(info);
	find_outfile(info);
	info->data = data;
	info->curr_cmd = 1;
	info->pipefd[0] = 0;
	info->pipefd[1] = 0;
	return ;
}

// void	make_path_checks(t_data *data)
// {
// 	int	path_no;

// 	ft_printf("make_path_checks\n");
// 	path_no = find_path_index(data->envp);
// 	ft_printf("path_no: %d\n", path_no);
// 	ft_printf("envp[path_no]: %s\n", data->envp[path_no]);
// 	if (data->envp[path_no] == NULL)
// 	{
// 		free_system(data);
// 		ft_print_error(ERROR_NULL_PATH);
// 		exit(ERROR_NULL_PATH);
// 	}
// 	if (path_no == 0)
// 	{
// 		free_system(data);
// 		ft_print_error(ERROR_CMD_NOT_FOUND);
// 		exit(ERROR_CMD_NOT_FOUND);
// 	}
// 	return ;
// }

int	pipex(t_data *data)
{
	t_pipex	*info;
	int		exit_code;
	int		pipe_count;

	ft_printf("pipex\n");
	info = (t_pipex *)ft_calloc(1, sizeof(t_pipex));
	if (info == NULL || errno == ENOMEM)
		ft_exit_data_perror(data, ERROR_ALLOCATION, "info in pipex");
	data->info = info;
	pipe_count = check_pipe(data->line);
	info->nbr_of_cmds = pipe_count + 1;
	printf("nbr_of_cmds: %d\n", info->nbr_of_cmds);
	initialize_cmds(data, info);
	initialize_info(info, data);
	// printf("infile: %s\n", info->infile);
	// printf("outfile: %s\n", info->outfile);
	printf("initilaization is done\n\n*******\n\n");
	exit_code = create_children(data);
	printf("exit_code: %d\n", exit_code);
	free_system(data);
	return (exit_code);
}
