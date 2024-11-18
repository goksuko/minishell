/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   semantic.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 22:40:37 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/11/18 11:56:38 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	handle_infile(t_data *data, t_info *info, int i, t_token *current)
{
	if (info->fds[i][0] != -10)
		ms_close(data, info->fds[i][0]);
	info->fds[i][0] = current->fd_in;
	info->fd_in = current->fd_in;
	info->infile = ms_strdup(data, current->expanded_value);
	return (true);
}

bool	handle_outfile(t_data *data, t_info *info, int i, t_token *current)
{
	if (info->fds[i][1] != -10)
		ms_close(data, info->fds[i][1]);
	info->fds[i][1] = current->fd_out;
	info->fd_out = current->fd_out;
	info->outfile = ms_strdup(data, current->expanded_value);
	return (true);
}

void	initialize_fds_array(t_info *info)
{
	int	i;

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
			if (!handle_outfile(data, info, i, current))
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
	data->exit_code = 0;
	data->nbr_of_pipes = find_pipe_count(data->tokens);
	data->nbr_of_cmds = data->nbr_of_pipes + 1;
	data->info->here_doc_cmd = -100;
	data->cmds = cmds_from_tokens(data);
	initialize_info(data->info, data);
	if (initialize_fds(data->info, data) == false)
		return (false);
	if (data->cmds == NULL)
		return (false);
	return (true);
}
