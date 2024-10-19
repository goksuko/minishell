/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   semantic_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 22:31:21 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/19 22:31:25 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_pipe_count(t_token *tokens)
{
	int		pipe_count;
	t_token	*current;

	pipe_count = 0;
	current = tokens;
	while (current)
	{
		if (current->type == T_PIPE)
			pipe_count++;
		current = current->next;
	}
	return (pipe_count);
}

void	initialize_info(t_info *info, t_data *data)
{
	info->data = data;
	info->curr_cmd = 0;
	info->pipe_read_end = STDIN_FILENO;
	return ;
}
