/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/22 15:18:43 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/11/18 16:58:03 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_redir(t_token *current)
{
	if (current && (current->type == T_SMALLER || current->type == T_GREATER
			|| current->type == T_DSMALLER || current->type == T_DGREATER))
		return (true);
	return (false);
}

bool	is_redir_except_heredoc(t_token *current)
{
	if (current && (current->type == T_SMALLER || current->type == T_GREATER
			|| current->type == T_DGREATER))
		return (true);
	return (false);
}

bool	is_heredoc(t_token *current)
{
	if (current->type == T_DSMALLER)
		return (true);
	return (false);
}

bool	heredoc_inside(t_token *current)
{
	while (current && current->type != T_DSMALLER)
		current = current->next;
	if (current)
		return (true);
	else
		return (false);
}

int	heredoc_position(t_token *current)
{
	int	i;

	i = 0;
	while (current)
	{
		while (current && current->type != T_PIPE && current->type != T_DSMALLER)
			current = current->next;
		if (current->type == T_DSMALLER)
			return (i);
		while (current && current->type != T_PIPE)
			current = current->next;
		if (current && current->type == T_PIPE)
		{
			i++;
			current = current->next; // to skip the pipe
		}
	}
	if (current == NULL)
		return (-15);
	return (i);
}
