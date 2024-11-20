/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_semantic.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 22:39:21 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/11/19 10:20:49 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	limiter_check(t_data *data)
{
	t_token	*current;
	int		i;

	i = 0;
	current = data->tokens;
	data->limiters = (char **)ms_calloc(data, sizeof(char *), (20));
	while (current)
	{
		if (current->limiter)
		{
			data->limiters[i] = ms_strdup(data, current->limiter);
			i++;
		}
		current = current->next;
	}
	data->limiters[i] = NULL;
	data->nbr_of_heredoc = i;
	return (true);
}

int	heredoc_fd_check(t_data *data)
{
	t_token	*current;
	int		temp_fd;

	current = data->tokens;
	while (current)
	{
		if (current->limiter)
			temp_fd = current->heredoc_fd;
		current = current->next;
	}
	return (temp_fd);
}

void	heredoc_helper(t_data *data, int heredoc_fd, int i)
{
	char	*limiter;
	char	*line;
	
	limiter = data->limiters[i];
	line = readline("> ");
	while (line)
	{
		if ((ft_strlen(line) == ft_strlen(limiter)) && ft_strncmp(line, limiter,
				ft_strlen(limiter)) == 0)
			break ;
		write(heredoc_fd, line, ft_strlen(line));
		write(heredoc_fd, "\n", 1);
		free_and_null(&line);
		line = readline("> ");
	}
}

bool	init_heredoc(t_data *data)
{
	int		i;

	handle_signals(HEREDOC);
	i = 0;
	if (limiter_check(data) == false)
		return (false);
	while (i < data->nbr_of_heredoc)
	{
		if (i != 0)
		{
			printf("i: %d\n", i);
			ms_close(data, data->heredoc_fd);
			data->heredoc_fd = ms_open(data, "0ur_h3r3_d0c", O_CREAT | O_TRUNC | O_WRONLY, 0777);
		}
		heredoc_helper(data, data->heredoc_fd, i);
		ms_close(data, data->heredoc_fd);
		i++;
	}
	return (true);
}
