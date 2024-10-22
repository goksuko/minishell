/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_semantic.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 22:39:21 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/22 14:12:25 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	limiter_check(t_data *data)
{
	t_token	*current;

	current = data->tokens;
	while (current)
	{
		if (current->limiter)
		{
			data->info->limiter = ft_strdup(current->limiter);
			if (data->info->limiter == NULL)
				return (error_assign(data, ERROR_ALLOCATION));
		}
		current = current->next;
	}
	return (SUCCESS);
}

int	here_doc_fd_check(t_data *data)
{
	t_token	*current;
	int		temp_fd;

	current = data->tokens;
	while (current)
	{
		if (current->limiter)
			temp_fd = current->here_doc_fd;
		current = current->next;
	}
	return (temp_fd);
}

int	init_heredoc(t_data *data)
{
	char	*limiter;
	char	*line;
	int		here_doc_fd;

	handle_signals(HEREDOC);
	here_doc_fd = here_doc_fd_check(data);
	if (limiter_check(data) > 0)
		return (data->exit_code);
	limiter = data->info->limiter;
	line = readline("> ");
	while (line)
	{
		if ((ft_strlen(line) == ft_strlen(limiter)) && ft_strncmp(line, limiter,
				ft_strlen(limiter)) == 0)
			break ;
		write(here_doc_fd, line, ft_strlen(line));
		write(here_doc_fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (close(here_doc_fd) < 0)
		return (error_assign(data, ERROR_CLOSE));
	free(line);
	return (SUCCESS);
}
