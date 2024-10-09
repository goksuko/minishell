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
		if (current->fd_in != -10)
		{
			info->fds[i][0] = current->fd_in;
			info->infile = current->value;
		}
		if (current->fd_out != -10)
		{
			info->fds[i][1] = current->fd_out;
			info->outfile = current->value;
		}
		if (current->type == T_PIPE)
			i++;
		current = current->next;
	}
	// printf("info->fds[0][0]: %d\n", info->fds[0][0]);
	// printf("info->fds[0][1]: %d\n", info->fds[0][1]);
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
	info->nbr_of_cmds = data->nbr_of_pipes + 1;
	data->info = info;
	// data->cmds = data->ast->argument;
	data->here_doc = NULL;
	//here_doc should be done after pipe
	if (is_heredoc(data->tokens))
	{
		do_heredoc(data);
		data->cmds = find_cmd_of_heredoc(data->tokens);
		// finish_heredoc(data);
	}
	else
		data->cmds = cmds_from_tokens(data);
	info->cmds = data->cmds;
	initialize_info(info, data);
	initialize_fds(info, data);
}
