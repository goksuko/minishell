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
			info->infile = ft_strdup(current->expanded_value);
			if (info->infile == NULL)
			{
				free_system_perror(data, ERROR_ALLOCATION, "info->infile in initialize_fds");
				return ; //false boolean
			}
		}
		if (current->fd_out != -10)
		{
			if (info->fds[i][1] != -10)
				close_safe(info->fds[i][1], info);
			info->fds[i][1] = current->fd_out;
			info->outfile = ft_strdup(current->expanded_value);
			if (info->outfile == NULL)
			{
				free_system_perror(data, ERROR_ALLOCATION, "info->outfile in initialize_fds");
				return ; //false boolean
			}
		}
		if (current->type == T_PIPE) // we write the fd_in and fd_out values (if there is) between pipes
			i++;
		current = current->next;
	}
}

bool	semantic_analysis(t_data *data)
{
	t_info	*info;

	data->exit_code = 0;
	data->nbr_of_tokens = count_tokens(data->line);
	data->nbr_of_pipes = find_pipe_count(data->tokens);
	info = (t_info *)ft_calloc(1, sizeof(t_info));
	if (info == NULL || errno == ENOMEM)
	{
		free_system_perror(data, ERROR_ALLOCATION, "info in semantic_analysis");
		return (false);
	}
	data->nbr_of_cmds = data->nbr_of_pipes + 1;
	data->info = info;
	data->info->limiter = NULL;
	data->info->here_doc_cmd = -100;
	data->cmds = cmds_from_tokens(data);
	if (data->cmds == NULL)
		return (false);
	initialize_info(info, data); //here
	initialize_fds(info, data);
	return (true);
}
