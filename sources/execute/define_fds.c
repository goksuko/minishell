#include "../../includes/minishell.h"

void define_redir_in(t_pipex *info, char **cmd_split, int i)
{
	int temp_fd;

	temp_fd = open(cmd_split[i + 1], O_RDONLY, 0777);
	if (temp_fd == -1)
	{
		close_pipex(info, NULL);
		ft_exit_data_perror(info->data, ERROR_FILE_OPEN, "temp_fd in define_redir_in");
	}
	info->fd_in = temp_fd;
	info->infile = ft_strdup(cmd_split[i + 1]);
	printf("< fd_in: %d, infile: %s\n", info->fd_in, info->infile);
}

void define_redir_out(t_pipex *info, char **cmd_split, int i)
{
	int temp_fd;

	temp_fd = open(cmd_split[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (temp_fd == -1)
	{
		close_pipex(info, NULL);
		ft_exit_data_perror(info->data, ERROR_FILE_OPEN, "temp_fd in define_redir_out");
	}
	info->fd_out = temp_fd;
	info->outfile = ft_strdup(cmd_split[i + 1]);
	printf("> fd_out: %d, outfile: %s\n", info->fd_out, info->outfile);
}

void define_redir_append(t_pipex *info, char **cmd_split, int i)
{
	int temp_fd;
	
	temp_fd = open(cmd_split[i + 1], O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (temp_fd == -1)
	{
		close_pipex(info, NULL);
		ft_exit_data_perror(info->data, ERROR_FILE_OPEN, "temp_fd in define_redir_append");
	}
	info->fd_out = temp_fd;
	info->outfile = ft_strdup(cmd_split[i + 1]);
	printf(">> fd_out: %d, outfile: %s\n", info->fd_out, info->outfile);
}

void define_redir_heredoc(t_pipex *info, char **cmd_split, int i)
{
	int temp_fd;
	
	temp_fd = open("our_here_doc", O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (temp_fd == -1)
	{
		close_pipex(info, NULL);
		ft_exit_data_perror(info->data, ERROR_FILE_OPEN, "temp_fd in define_heredoc");
	}
	info->fd_out = temp_fd;
	info->outfile = ft_strdup("our_here_doc");
	if (ft_strlen(cmd_split[i]) == 2)
	{
		info->limiter = ft_strdup(cmd_split[i + 1]);
		if (info->limiter == NULL || errno == ENOMEM)
			ft_exit_data_perror(info->data, ERROR_ALLOCATION, "info->limiter in define_redir_heredoc");
	}
	else
	{
		info->limiter = ft_strdup(cmd_split[i] + 2);
		if (info->limiter == NULL || errno == ENOMEM)
			ft_exit_data_perror(info->data, ERROR_ALLOCATION, "info->limiter in define_redir_heredoc");
	}
	printf("<< fd_out: %d, outfile: %s\n", info->fd_out, info->outfile);
	printf("limiter: %s\n", info->limiter);
}

// when limiter comes, we have to finish the heredoc
void finish_redir_heredoc(t_pipex *info)
{
	int		exit_code;

	printf("finish_redir_heredoc\n");
	info->fd_in = open("our_here_doc", O_RDONLY, 0777);
	if (info->fd_in == -1)
	{
		close_pipex(info, NULL);
		ft_exit_data_perror(info->data, ERROR_FILE_OPEN, "info->fd_in in finish_redir_heredoc");
	}
	info->infile = ft_strdup("our_here_doc");
	if (info->infile == NULL || errno == ENOMEM)
		ft_exit_data_perror(info->data, ERROR_ALLOCATION, "info->infile in finish_redir_heredoc");
	info->fd_out = -10;
	info->outfile = NULL;
	exit_code = create_children(info->data);
	unlink("our_here_doc");
	printf("exit_code: %d\n", exit_code);
	info->data->exit_code = exit_code;
}


void define_fd_in_out(t_pipex *info)
{
	char **cmd_split;
	int		i;
	int		 j;
	// int		temp_fd;

	printf("define_fd_in_out\n");
	info->fd_in = -10;
	info->fd_out = -10;
	info->infile = NULL;
	info->outfile = NULL;

	cmd_split = ft_split(info->cmds[info->curr_cmd - 1], ' ');
	if (cmd_split == NULL || errno == ENOMEM)
		ft_exit_data_perror(info->data, ERROR_ALLOCATION, "cmd_split in define_fd_in_out");
	i = 0;
	while (cmd_split[i] != NULL)
	{
		if (ft_strnstr(cmd_split[i], ">>", 2) != NULL)
			define_redir_append(info, cmd_split, i);
		else if (ft_strnstr(cmd_split[i], ">", 1) != NULL)
			define_redir_out(info, cmd_split, i);
		else if (ft_strnstr(cmd_split[i], "<<", 2) != NULL)
			define_redir_heredoc(info, cmd_split, i);
		else if (ft_strnstr(cmd_split[i], "<", 1) != NULL)
		{
			define_redir_in(info, cmd_split, i);
			if (cmd_split[i + 2] != NULL)
			{
				j = i + 2;
				if (info->special_command != NULL)
					printf("special_command: %s\n", info->special_command);
				else
					printf("special_command is NULL\n");
				while (cmd_split[j] != NULL && cmd_split[j][0] != '>')
				{
					if (info->special_command == NULL)
					{
						info->special_command = ft_strdup(cmd_split[j]);
						if (info->special_command == NULL || errno == ENOMEM)
							ft_exit_data_perror(info->data, ERROR_ALLOCATION, "ft_strdup in define_fd_in_out");
					}
					else
					{
						info->special_command = ft_strjoin(info->special_command, cmd_split[j]);
						if (info->special_command == NULL || errno == ENOMEM)
							ft_exit_data_perror(info->data, ERROR_ALLOCATION, "ft_strjoin in define_fd_in_out");
					}
					j++;
				}
				if (info->special_command != NULL)
					printf("special_command: %s\n", info->special_command);
				else
					printf("special_command is NULL\n");
				while (cmd_split[j] != NULL)
				{
					if (ft_strnstr(cmd_split[j], ">>", ft_strlen(cmd_split[j])) != NULL)
						define_redir_append(info, cmd_split, j);
					else if (ft_strnstr(cmd_split[j], ">", ft_strlen(cmd_split[j])) != NULL)
						define_redir_out(info, cmd_split, j);
					j++;
				}
				
			}
		}
		i++;
	}
	return ;
}
