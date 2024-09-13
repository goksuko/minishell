/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/16 13:36:47 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/09/13 19:22:38 by akaya-oz      ########   odam.nl         */
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

// pid_t	child_process(t_pipex *info)
// {
// 	pid_t	pid;

// 	printf("child_process\n");
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		close_pipex(info, NULL);
// 		ft_exit_perror(ERROR_FORK, "fork in child process");
// 	}
// 	if (pid == 0)
// 	{
// 		printf("curr_cmd: %d\n", info->curr_cmd);
// 		printf("pipefd[0]: %d\n", info->pipefd[0]);
// 		printf("pipefd[1]: %d\n", info->pipefd[1]);
// 		if (info->fd_in != -10)
// 		{
// 			dup2_safe(info->fd_in, STDIN_FILENO, info); // it was fd_in before actually
// 			close_safe(info->fd_in, info);
// 		}
// 		else if (info->curr_cmd != 1)
// 		{
// 			dup2_safe(info->pipe_read_end, STDIN_FILENO, info);
// 			close_safe(info->pipe_read_end, info);
// 		}
// 		if (info->curr_cmd == 1 && info->fd_in == -10) // added this condition
// 			dup2_safe(info->pipefd[0], STDIN_FILENO, info);
// 		close_safe(info->pipefd[0], info);
// 		if (info->curr_cmd == 1 && info->fd_out == -10)
// 			dup2_safe(info->pipefd[1], STDOUT_FILENO, info);
// 		else
// 			dup2_safe(info->fd_out, STDOUT_FILENO, info);
// 		close_safe(info->pipefd[1], info);
// 		info->pipe_read_end = info->pipefd[0];
// 		printf("ready to start exec\n");
// 		start_exec(info);
// 	}
// 	return (pid);
// }

void do_first_child(t_pipex *info)
{
	printf("do_first_child\n");
	if (info->fd_in != -10)
	{
		dup2_safe(info->fd_in, STDIN_FILENO, info); // it was fd_in before actually
		// close_safe(info->fd_in, info);
		// close_safe(info->pipefd[0], info);
	}
	if (info->fd_out != -10)
	{
		dup2_safe(info->fd_out, STDOUT_FILENO, info);
		// close_safe(info->fd_out, info);
	}
	else
	{
		dup2_safe(info->pipefd[1], STDOUT_FILENO, info);
	}
	// close_safe(info->pipefd[1], info);
	// info->pipe_read_end = info->pipefd[1];
}

void do_middle_child(t_pipex *info)
{
	printf("do_middle_child\n");
	if (info->fd_in != -10)
	{
		dup2_safe(info->fd_in, STDIN_FILENO, info); // it was fd_in before actually
		// close_safe(info->fd_in, info);
	}
	else
	{
		printf("pipe_read_end in middle child: %d\n", info->pipe_read_end);
		dup2_safe(info->pipe_read_end, STDIN_FILENO, info);
		// close_safe(info->pipe_read_end, info);
	}
	if (info->fd_out != -10)
	{
		dup2_safe(info->fd_out, STDOUT_FILENO, info);
		// close_safe(info->fd_out, info);
	}
	else
	{
		dup2_safe(info->pipefd[1], STDOUT_FILENO, info);
	}
	// close_safe(info->pipefd[1], info);
	// info->pipe_read_end = info->pipefd[1];
}

void do_last_child(t_pipex *info)
{
	printf("do_last_child\n");
	if (info->fd_out != -10)
	{
		dup2_safe(info->fd_out, STDOUT_FILENO, info);
		// close_safe(info->fd_out, info);
	}
	if (info->fd_in != -10)
	{
		dup2_safe(info->fd_in, STDIN_FILENO, info);
		// close_safe(info->fd_in, info); //ben kapattim
	}
	else if (info->curr_cmd != 1)
	{
		printf("pipe_read_end in last child: %d\n", info->pipe_read_end);
		dup2_safe(info->pipe_read_end, STDIN_FILENO, info);
		// close_safe(info->pipe_read_end, info);
	}

	// close_safe(info->pipefd[1], info);
}

pid_t	child_process(t_pipex *info)
{
	pid_t	pid;

	printf("--child_process--\n");
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

		if (info->curr_cmd == info->nbr_of_cmds)
			do_last_child(info);
		else if (info->curr_cmd == 1)
			do_first_child(info);
		else
			do_middle_child(info);
		if (info->fd_out != -10)
		{
			close_safe(info->fd_out, info);
		}
		if (info->fd_in != -10)
		{
			close_safe(info->fd_in, info);
		}
		close_safe(info->pipefd[1], info);
		if (info->pipe_read_end != STDIN_FILENO)
			close_safe(info->pipe_read_end, info);
		// info->pipe_read_end = info->pipefd[0];
		printf("---pipe_read_end in loop: %d\n", info->pipe_read_end);

		// if (info->fd_in != -10)
		// {
		// 	dup2_safe(info->fd_in, STDIN_FILENO, info); // it was fd_in before actually
		// 	close_safe(info->fd_in, info);
		// }
		// else if (info->curr_cmd != 1)
		// {
		// 	dup2_safe(info->pipe_read_end, STDIN_FILENO, info);
		// 	close_safe(info->pipe_read_end, info);
		// }
		// if (info->curr_cmd == 1 && info->fd_in == -10) // added this condition
		// 	dup2_safe(info->pipefd[0], STDIN_FILENO, info);
		// close_safe(info->pipefd[0], info);
		// if (info->curr_cmd == 1 && info->fd_out == -10)
		// 	dup2_safe(info->pipefd[1], STDOUT_FILENO, info);
		// else
		// 	dup2_safe(info->fd_out, STDOUT_FILENO, info);
		// close_safe(info->pipefd[1], info);
		// info->pipe_read_end = info->pipefd[0];
		printf("ready to start exec\n");
		start_exec(info);
	}
	return (pid);
}

// pid_t	last_child_process(t_pipex *info)
// {
// 	pid_t	pid;

// 	printf("\n----last_child_process\n");
// 	pid = fork();
// 	if (pid == -1)
// 		ft_exit_perror(ERROR_FORK, "fork in last child process");
// 	if (pid == 0)
// 	{
// 		printf("pipefd[0]: %d\n", info->pipefd[0]);
// 		printf("pipefd[1]: %d\n", info->pipefd[1]);
// 		printf("fd_in: %d\n", info->fd_in);
// 		printf("fd_out: %d\n", info->fd_out);
// 		// close_safe(info->pipefd[1], info);
// 		// dup2_safe(info->pipefd[0], STDIN_FILENO, info);
// 		// close_safe(info->pipefd[0], info);
// 		if (info->fd_out != -10)
// 		{
// 			dup2_safe(info->fd_out, STDOUT_FILENO, info);
// 			close_safe(info->fd_out, info);
// 		}
// 		if (info->fd_in != -10)
// 		{
// 			dup2_safe(info->fd_in, STDIN_FILENO, info);
// 			close_safe(info->fd_in, info);
// 		}
// 		else
// 		{
// 			dup2_safe(info->pipe_read_end, STDIN_FILENO, info);
// 			close_safe(info->pipe_read_end, info);
// 		}
// 		// dup2_safe(info->fd_out, STDOUT_FILENO, info);
// 		// close_safe(info->fd_out, info);
// 		// close_safe(info->pipefd[1], info);
// 		// close_safe(info->pipefd[0], info);
// 		printf("ready to start last exec\n");
// 		// printf_array(info->cmds);
// 		start_exec(info);
// 	}
// 	return (pid);
// }

void define_fd_in_out(t_pipex *info)
{
	char **cmd_split;
	int		i;
	int		temp_fd;

	printf("define_fd_in_out\n");
	cmd_split = ft_split(info->cmds[info->curr_cmd - 1], ' ');
	if (cmd_split == NULL || errno == ENOMEM)
		ft_exit_data_perror(info->data, ERROR_ALLOCATION, "cmd_split in define_fd_in_out");
	i = 0;
	while (cmd_split[i] != NULL)
	{
		if (ft_strnstr(cmd_split[i], ">", ft_strlen(cmd_split[i])) != NULL)
		{
			temp_fd = open(cmd_split[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0777);
			if (temp_fd == -1)
			{
				close_pipex(info, NULL);
				ft_exit_data_perror(info->data, ERROR_FILE_OPEN, "outfile in fill_fds");
			}
			info->fd_out = temp_fd;
			printf("> fd_out: %d\n", info->fd_out);
		}
		else
			info->fd_out = -10;
		if (ft_strnstr(cmd_split[i], "<", ft_strlen(cmd_split[i])) != NULL)
		{
			temp_fd = open(cmd_split[i + 1], O_RDONLY, 0777);
			if (temp_fd == -1)
			{
				close_pipex(info, NULL);
				ft_exit_data_perror(info->data, ERROR_FILE_OPEN, "infile in fill_fds");
			}
			info->fd_in = temp_fd;
		}
		else
			info->fd_in = -10;
		if (ft_strnstr(cmd_split[i], ">>", ft_strlen(cmd_split[i])) != NULL)
		{
			temp_fd = open(cmd_split[i + 1], O_CREAT | O_APPEND | O_WRONLY, 0777);
			if (temp_fd == -1)
			{
				close_pipex(info, NULL);
				ft_exit_data_perror(info->data, ERROR_FILE_OPEN, "outfile in fill_fds");
			}
			info->fd_out = temp_fd;
		}
		else
			info->fd_out = -10;
		i++;
	}
	return ;
}

// int	create_children(t_data *data)
// {
// 	int		i;
// 	pid_t	pid;
// 	pid_t	pid_last;
// 	int		status;

// 	printf("---create_children---\n");
// 	i = 1;
// 	printf("nbr_of_cmds: %d\n\n", data->nbr_of_cmds);
// 	while (i < data->nbr_of_cmds)
// 	{
// 		printf("\nin while loop i: %d\n", i);
// 		define_fd_in_out(data->info);
// 		if (pipe(data->info->pipefd) == -1)
// 			ft_close_exit_perror(data->info, NULL, ERROR_PIPE, "pipe in create children");
// 		if (data->info->pipe_read_end != STDIN_FILENO)
// 			close(data->info->pipe_read_end);
// 		data->info->pipe_read_end = data->info->pipefd[0];
// 		printf("curr_cmd before child: %d\n", data->info->curr_cmd);
// 		pid = child_process(data->info);
// 		close_safe(data->info->pipefd[1], data->info);
// 		dup2_safe(data->info->pipefd[0], STDIN_FILENO, data->info);
// 		close_safe(data->info->pipefd[0], data->info);
// 		data->info->curr_cmd++;
// 		printf("curr_cmd after child: %d\n", data->info->curr_cmd);
// 		i++;
// 		printf("sleeping after child (%d)\n", i);
// 		sleep(1);
// 	}
// 	printf("\nsleeping before last child\n");
// 	sleep(1);
// 	define_fd_in_out(data->info);
// 	printf("curr_cmd before last child: %d\n", data->info->curr_cmd);
// 	pid_last = last_child_process(data->info);
// 	while (waitpid(pid, &status, 0) != -1);
// 	waitpid(pid_last, &status, 0);
// 	if (WIFEXITED(status))
// 		return (WEXITSTATUS(status));
// 	return (SUCCESS);
// }



int	create_children(t_data *data)
{
	int		i;
	pid_t	pid;
	// pid_t	pid_last;
	int		status;

	printf("---create_children---\n");
	i = 1;
	data->info->pipe_read_end = STDIN_FILENO;
	printf("nbr_of_cmds: %d\n**********\n", data->nbr_of_cmds);
	while (i <= data->nbr_of_cmds)
	{
		printf("\nin while loop i: %d\n", i);
		define_fd_in_out(data->info);
		if (i != data->nbr_of_cmds)
		{
			if (pipe(data->info->pipefd) == -1)
				ft_close_exit_perror(data->info, NULL, ERROR_PIPE, "pipe in create children");
		}
		// if (data->info->pipe_read_end != STDIN_FILENO)
		// 	close_safe(data->info->pipe_read_end, data->info);
		// if (data->info->pipe_read_end != STDIN_FILENO)
		// 	close(data->info->pipe_read_end);
		// data->info->pipe_read_end = data->info->pipefd[0];

		// printf("curr_cmd before child: %d\n", data->info->curr_cmd);
		pid = child_process(data->info);
		data->info->pipe_read_end = data->info->pipefd[0];
		// close_safe(data->info->pipefd[1], data->info);
		// dup2_safe(data->info->pipefd[0], STDIN_FILENO, data->info);
		// close_safe(data->info->pipefd[0], data->info);
		data->info->curr_cmd++;
		// printf("curr_cmd after child: %d\n", data->info->curr_cmd);
		// i++;
		printf("sleeping after child (%d)\n", i);
		sleep(1);
		i++;
	}
	// printf("\nsleeping before last child\n");
	// sleep(1);
	// define_fd_in_out(data->info);
	// printf("curr_cmd before last child: %d\n", data->info->curr_cmd);
	// pid_last = last_child_process(data->info);
	// while (waitpid(pid, &status, 0));
	waitpid(pid, &status, 0);
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (SUCCESS);
}

char **clean_spaces(char **matrix)
{
	int		i;
	// char	*temp;

	i = 0;
	while (matrix[i] != NULL)
	{
		// if (matrix[i][1] != '\0' && matrix[i][0] == ' ')
		// {
		// 	temp = ft_strdup(matrix[i] + 1);
		// 	if (temp == NULL || errno == ENOMEM)
		// 		ft_exit_perror(ERROR_ALLOCATION, "temp in clean_first_spaces");
		// 	free(matrix[i]);
		// 	matrix[i] = temp;
		// }
		matrix[i] = ft_strtrim(matrix[i], " ");
		i++;
	}
	return (matrix);
}

// void	fill_fds(int *fds, char **cmd_split, t_pipex *info)
// {
// 	int		i;
// 	int		temp_fd;

// 	i = 0;
// 	while (cmd_split[i] != NULL)
// 	{
// 		if (ft_strnstr(cmd_split[i], ">", ft_strlen(cmd_split[i])) != NULL)
// 		{
// 			temp_fd = open(cmd_split[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0777);
// 			if (temp_fd == -1)
// 			{
// 				close_pipex(info, NULL);
// 				ft_exit_data_perror(info->data, ERROR_FILE_OPEN, "outfile in fill_fds");
// 			}
// 			fds[1] = temp_fd;
// 			printf("> fds[1]: %d\n", fds[1]);
// 		}
// 		else
// 			fds[1] = STDOUT_FILENO;
// 		if (ft_strnstr(cmd_split[i], "<", ft_strlen(cmd_split[i])) != NULL)
// 		{
// 			temp_fd = open(cmd_split[i + 1], O_RDONLY, 0777);
// 			if (temp_fd == -1)
// 			{
// 				close_pipex(info, NULL);
// 				ft_exit_data_perror(info->data, ERROR_FILE_OPEN, "infile in fill_fds");
// 			}
// 			fds[0] = temp_fd;
// 		}
// 		else
// 			fds[0] = STDIN_FILENO;
// 		if (ft_strnstr(cmd_split[i], ">>", ft_strlen(cmd_split[i])) != NULL)
// 		{
// 			temp_fd = open(cmd_split[i + 1], O_CREAT | O_APPEND | O_WRONLY, 0777);
// 			if (temp_fd == -1)
// 			{
// 				close_pipex(info, NULL);
// 				ft_exit_data_perror(info->data, ERROR_FILE_OPEN, "outfile in fill_fds");
// 			}
// 			fds[1] = temp_fd;
// 		}
// 		else
// 			fds[1] = STDOUT_FILENO;
// 		i++;
// 	}
// 	return ;
// }

// void find_fds(char *line, t_pipex *info)
// {
// 	int		i;
// 	char	**cmds;
// 	char	**cmd_split;

// 	i = 0;
// 	printf("------find_fds------\n");
// 	ft_memset(info->fds, 0, sizeof(info->fds));
// 	cmds = ft_split(line, '|');
// 	if (cmds == NULL || errno == ENOMEM)
// 		ft_exit_perror(ERROR_ALLOCATION, "cmds in find_fds");
// 	while (cmds[i] != NULL)
// 	{
// 		cmd_split = ft_split(cmds[i], ' ');
// 		if (cmd_split == NULL || errno == ENOMEM)
// 			ft_exit_perror(ERROR_ALLOCATION, "cmd_split in find_fds");
// 		fill_fds(info->fds[i], cmd_split, info);
// 		printf("fds[%d][0]: %d\n", i, info->fds[i][0]);
// 		printf("fds[%d][1]: %d\n", i, info->fds[i][1]);
// 		free_matrix(cmd_split);
// 		i++;
// 	}
// 	free_matrix(cmds);
// 	return ;
// }

char **clean_up_to_redir(char **matrix)
{
	int		i;
	char	**temp;

	i = 0;
	while (matrix[i] != NULL)
		i++;
	temp = ft_calloc(sizeof(char *), i + 1);
	if (temp == NULL || errno == ENOMEM)
		ft_exit_perror(ERROR_ALLOCATION, "temp in clean_up_to_redir");
	i = 0;
	while (matrix[i] != NULL)
	{
		if (matrix[i][0] == '<' || matrix[i][0] == '>')
		{
			temp[i] = NULL;
			break;
		}
		else
		{
			temp[i] = ft_strdup(matrix[i]);
			if (temp[i] == NULL || errno == ENOMEM)
				ft_exit_perror(ERROR_ALLOCATION, "temp[i] in clean_up_to_redir");
		}
		i++;
	}
	free_matrix(matrix);
	return (temp);
}

void	initialize_cmds(t_data *data, t_pipex *info)
{
	char	**cmds;

	ft_printf("---initialize_cmds---\n");
	cmds = ft_split(data->line, '|');
	cmds = clean_spaces(cmds);
	// cmds = clean_up_to_redir(cmds); //wromg place
	// printf_array(cmds);
	// cmds = data->ast->argument;
	// if (cmds)
	// 	printf_array(cmds);
	// else
	// 	printf("cmds is NULL\n");
	if (cmds == NULL || errno == ENOMEM)
		ft_exit_data_perror(data, ERROR_ALLOCATION, "cmds in initialize");
	// data->cmds = cmds;
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
	if (info->nbr_of_cmds == 1)
	{
		info->outfile = NULL;
		info->fd_out = STDOUT_FILENO;
		return (NULL);
	}
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
	ft_printf("\n---initialize_info---\n");
	info->path_from_getenv = getenv("PATH");
	if (info->path_from_getenv == NULL)
	{
		close_pipex(info, NULL);
		ft_exit_data_error(data, ERROR_NULL_PATH);
	}
	// printf("path_from_getenv: %s\n", info->path_from_getenv);
	// find_infile(info);
	// find_outfile(info);
	info->data = data;
	info->curr_cmd = 1;
	info->pipe_read_end = STDIN_FILENO;
	// info->pipefd[0] = 0;
	// info->pipefd[1] = 0;
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
	// pipe_count = check_pipe(data->line);
	pipe_count = data->nbr_of_pipes;
	info->nbr_of_cmds = pipe_count + 1;
	printf("pipe_count: %d\n", pipe_count);
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

// cat | cat | ls -l | wc -l
// cat | cat | ls

// valgrind --track-fds=yes --leak-check=full ./minishell 
// if opened before fork, close both in parent and child

// cat main.c > out
// < main.c cat > out
//  cat < main.c > out

// akaya-oz@f0r3s18:~/codam/minishell$ echo $HOME
// /home/akaya-oz
// akaya-oz@f0r3s18:~/codam/minishell$ <<eof cat
// > $HOME
// > bla
// > eof
// /home/akaya-oz
// bla
