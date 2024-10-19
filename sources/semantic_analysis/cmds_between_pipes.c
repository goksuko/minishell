/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds_between_pipes.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 22:34:41 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/19 22:43:33 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	handle_heredoc(t_token **current, char **cmds, int *j)
{
	if ((*current)->next && (*current)->next->next)
		(*current) = (*current)->next->next;
	cmds[*j] = ft_strdup((*current)->expanded_value);
	if (cmds[*j] == NULL)
		return (false);
	(*current) = (*current)->next;
	while ((*current) && (*current)->type != T_PIPE)
	{
		cmds[*j] = ft_strjoin(cmds[*j], " ");
		if (cmds[*j] == NULL)
			return (false);
		cmds[*j] = ft_strjoin(cmds[*j], (*current)->expanded_value);
		if (cmds[*j] == NULL)
			return (false);
		(*current) = (*current)->next;
	}
	return (true);
}

bool	handle_redirection(t_token **current, bool *cat_cmd)
{
	if (is_redir_except_heredoc(*current) && is_first_after_pipe(*current))
	{
		*current = redir_first(*current);
		if (!*current)
			return (false);
	}
	if (*current && ft_strncmp((*current)->expanded_value, "cat", 3) == 0)
		*cat_cmd = true;
	return (true);
}

bool	handle_redirection2(t_token **current, char **cmds, int *j,
		bool *cat_cmd)
{
	if (is_first_after_pipe(*current))
	{
		cmds[*j] = ft_strdup((*current)->expanded_value);
		if (cmds[*j] == NULL)
			return (false);
		(*current) = (*current)->next;
	}
	if ((*current) && is_redir_except_heredoc(*current))
	{
		if (*cat_cmd)
		{
			cmds[*j] = do_cat_addition(*current, cmds[*j]);
			if (cmds[*j] == NULL)
				return (false);
			*cat_cmd = false;
		}
		(*current) = (*current)->next->next;
	}
	return (true);
}

bool	handle_command(t_token **current, char **cmds, int *j)
{
	if ((*current) && (*current)->type != T_PIPE)
	{
		cmds[*j] = ft_strjoin(cmds[*j], " ");
		if (cmds[*j] == NULL)
			return (false);
		cmds[*j] = ft_strjoin(cmds[*j], (*current)->expanded_value);
		if (cmds[*j] == NULL)
			return (false);
		(*current) = (*current)->next;
	}
	return (true);
}

bool	handle_loop(t_token **current, char **cmds, int *j, bool *cat_cmd)
{
	while ((*current) && (*current)->type != T_PIPE)
	{
		if (is_heredoc(*current))
		{
			if (!handle_heredoc(current, cmds, j))
				return (false);
		}
		if (!handle_redirection(current, cat_cmd))
			return (false);
		if (!handle_redirection2(current, cmds, j, cat_cmd))
			return (false);
		if (!handle_command(current, cmds, j))
			return (false);
	}
	return (true);
}
