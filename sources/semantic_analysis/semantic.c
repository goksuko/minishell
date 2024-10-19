#include "../../includes/minishell.h"

bool	handle_infile(t_data *data, t_info *info, int i, t_token *current)
{
	if (info->fds[i][0] != -10)
	{
		if (close(info->fds[i][0]) < 0)
		{
			free_system_perror(data, ERROR_CLOSE,
				"info->fds[i][0] in initialize_fds");
			return (false);
		}
	}
	info->fds[i][0] = current->fd_in;
	info->infile = ft_strdup(current->expanded_value);
	if (info->infile == NULL)
	{
		free_system_perror(data, ERROR_ALLOCATION,
			"info->infile in initialize_fds");
		return (false);
	}
	return (true);
}

bool	handle_outfile(t_data *data, t_info *info, int i, t_token *current)
{
	if (info->fds[i][1] != -10)
	{
		if (close(info->fds[i][1]) < 0)
		{
			free_system_perror(data, ERROR_CLOSE,
				"info->fds[i][1] in initialize_fds");
			return (false);
		}
	}
	info->fds[i][1] = current->fd_out;
	info->outfile = ft_strdup(current->expanded_value);
	if (info->outfile == NULL)
	{
		free_system_perror(data, ERROR_ALLOCATION,
			"info->outfile in initialize_fds");
		return (false);
	}
	return (true);
}

void initialize_fds_array(t_info *info)
{
	int i;

	i = 0;
	while (i < 100)
	{
		info->fds[i][0] = -10;
		info->fds[i][1] = -10;
		i++;
	}
	return ;
}

bool	initialize_fds(t_info *info, t_data *data)
{
	int		i;
	t_token	*current;

	initialize_fds_array(info);
	i = 0;
	current = data->tokens;
	while (current)
	{
		if (current->fd_in != -10)
		{
			if (!handle_infile(data, info, i, current))
				return (false);
		}
		if (current->fd_out != -10)
		{
			if (!handle_outfile (data, info, i, current))
				return (false);
		}
		if (current->type == T_PIPE)
			i++;
		current = current->next;
	}
	return (true);
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
	initialize_info(info, data);
	if (initialize_fds(info, data) == false)
		return (false);
	return (true);
}
