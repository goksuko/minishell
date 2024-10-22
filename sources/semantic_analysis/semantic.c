/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   semantic.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 22:40:37 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/22 21:37:09 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_infile(t_data *data, t_info *info, int i, t_token *current)
{
	if (info->fds[i][0] != -10)
	{
		if (close(info->fds[i][0]) < 0)
		{
			free_system_perror(data, ERROR_CLOSE,
				"info->fds[i][0] in initialize_fds");
			return (error_assign(data, ERROR_CLOSE));
		}
	}
	info->fds[i][0] = current->fd_in;
	info->infile = ft_strdup(current->expanded_value);
	if (info->infile == NULL)
	{
		free_system_perror(data, ERROR_ALLOCATION,
			"info->infile in initialize_fds");
		return (error_assign(data, ERROR_ALLOCATION));
	}
	return (SUCCESS);
}

int	handle_outfile(t_data *data, t_info *info, int i, t_token *current)
{
	if (info->fds[i][1] != -10)
	{
		if (close(info->fds[i][1]) < 0)
		{
			free_system_perror(data, ERROR_CLOSE,
				"info->fds[i][1] in initialize_fds");
			return (error_assign(data, ERROR_CLOSE));
		}
	}
	info->fds[i][1] = current->fd_out;
	info->outfile = ft_strdup(current->expanded_value);
	if (info->outfile == NULL)
	{
		free_system_perror(data, ERROR_ALLOCATION,
			"info->outfile in initialize_fds");
		return (error_assign(data, ERROR_ALLOCATION));
	}
	return (SUCCESS);
}

int	handle_heredoc_outfile(t_data *data, t_token *current)
{
	current = current->next;
	while (current)
	{
		if (current->fd_out != -10)
		{
			if (data->here_doc_outfile_fd != -10)
			{
				if (close(data->here_doc_outfile_fd) < 0)
				{
					free_system_perror(data, ERROR_CLOSE,
						"data->here_doc_outfile_fd in initialize_fds");
					return (error_assign(data, ERROR_CLOSE));
				}
			}
			data->here_doc_outfile_fd = current->fd_out;
		}
		current = current->next;
	}
	return (SUCCESS);
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

int	initialize_fds(t_info *info, t_data *data)
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
			if (handle_infile(data, info, i, current) > 0)
				return (data->exit_code);
		}
		if (current->fd_out != -10)
		{
			if (handle_outfile(data, info, i, current) > 0)
				return (data->exit_code);
		}
		if (current->type == T_DSMALLER)
		{
			if (handle_heredoc_outfile(data, current) > 0)
				return (data->exit_code);
		}
		if (current->type == T_PIPE)
			i++;
		current = current->next;
	}
	return (SUCCESS);
}

int	semantic_analysis(t_data *data)
{
	t_info	*info;

	data->exit_code = 0;
	data->nbr_of_tokens = count_tokens(data->line);
	data->nbr_of_pipes = find_pipe_count(data->tokens);
	info = (t_info *)ft_calloc(1, sizeof(t_info));
	if (info == NULL || errno == ENOMEM)
	{
		free_system_perror(data, ERROR_ALLOCATION, "info in semantic_analysis");
		return (error_assign(data, ERROR_ALLOCATION));
	}
	data->nbr_of_cmds = data->nbr_of_pipes + 1;
	data->info = info;
	data->info->limiter = NULL;
	// data->info->here_doc_cmd = -100;
	data->cmds = cmds_from_tokens(data);
	if (data->cmds == NULL)
		return (data->exit_code);
	initialize_info(info, data);
	if (initialize_fds(info, data) > 0)
		return (data->exit_code);
	return (SUCCESS);
}
