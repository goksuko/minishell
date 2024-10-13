#include "../../includes/minishell.h"

void	initialize_fds(t_info *info, t_data *data)
{
	int		i;
	t_token	*current;

	printf("---initialize_fds---\n");
	i = 0;
	while (i < 100)
	{
		info->fds[i][0] = -10;
		info->fds[i][1] = -10;
		i++;
	}
	i = 0;
	current = data->tokens;
	while (current)
	{
		// if (current->fd_in != -10)
		// 	printf("current->fd_in: %d\n", current->fd_in);
		// if (current->fd_out != -10)
		// 	printf("current->fd_out: %d\n", current->fd_out);
		if (current->fd_in != -10) // if there is a redir, fd_in and fd_out is defined from tokens
		{
			if (info->fds[i][0] != -10)
				close_safe(info->fds[i][0], info);
			info->fds[i][0] = current->fd_in;
			info->infile = current->value;
		}
		if (current->fd_out != -10)
		{
			if (info->fds[i][1] != -10)
				close_safe(info->fds[i][1], info);
			info->fds[i][1] = current->fd_out;
			info->outfile = current->value;
		}
		if (current->type == T_PIPE) // we write the fd_in and fd_out values (if there is) between pipes
			i++;
		current = current->next;
	}
}

void	semantic_analysis(t_data *data)
{
	t_info	*info;

	printf("---SEMANTIC ANALYSIS---\n");
	data->exit_code = 0;
	data->nbr_of_tokens = count_tokens(data->line);
	data->nbr_of_pipes = find_pipe_count(data->tokens);
	printf("nbr_of_pipes: %d\n", data->nbr_of_pipes);
	info = (t_info *)ft_calloc(1, sizeof(t_info));
	if (info == NULL || errno == ENOMEM)
		ft_exit_data_perror(data, ERROR_ALLOCATION, "info in info");
	data->nbr_of_cmds = data->nbr_of_pipes + 1;
	printf("nbr_of_cmds: %d\n", data->nbr_of_cmds);
	data->info = info;
	// data->cmds = data->ast->argument;
	//here_doc should be done after pipe
	data->info->limiter = NULL;
	data->info->here_doc_cmd = -100;
	// if (heredoc_inside(data->tokens)) // commented to change the edge case of heredoc after pipe
	// {
	// 	printf("inside\n");
	// 	printf("fd_in: %d\n", data->info->fd_in);
	// 	printf("fd_out: %d\n", data->info->fd_out);		
	// 	init_heredoc(data);
	// 	close_safe(data->info->fd_out, data->info);
	// 	data->info->fd_out = STDOUT_FILENO;
	// 	data->info->fd_in = open("0ur_h3r3_d0c", O_RDONLY, 0777);
	// 	if (data->info->fd_in == -1)
	// 		ft_exit_data_perror(data, ERROR_FILE_OPEN, "0ur_h3r3_d0c");
	// }
	data->cmds = cmds_from_tokens(data);
	// printf("cmds_from_tokens\n");
	// printf_array(data->cmds);
	// info->cmds = data->cmds;
	initialize_info(info, data);
	initialize_fds(info, data);
}
