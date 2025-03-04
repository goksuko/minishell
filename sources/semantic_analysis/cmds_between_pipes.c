/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds_between_pipes.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 22:34:41 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/11/25 14:06:35 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	handle_heredoc(t_data *data, t_token **current, char **cmds, int *j)
{
	if ((*current)->next && (*current)->next->next)
		(*current) = (*current)->next->next;
	cmds[*j] = ms_strdup(data, (*current)->expanded_value);
	(*current) = (*current)->next;
	while ((*current) && (*current)->type != T_PIPE)
	{
		cmds[*j] = ms_strjoin(data, cmds[*j], " ");
		cmds[*j] = ms_strjoin(data, cmds[*j], (*current)->expanded_value);
		(*current) = (*current)->next;
	}
	return (true);
}

bool	handle_redirection(t_token **current, bool *cat_cmd, bool *no_cmd)
{
	if (is_redir_except_heredoc(*current) && is_first_after_pipe(*current))
	{
		if ((*current)->next == NULL || (*current)->next->type == T_PIPE || (*current)->next->next == NULL || (*current)->next->next->type == T_PIPE)	
		{
			*no_cmd = true;
		}
		else
		{
			*current = redir_first(*current);
			if (!*current)
				return (false);
		}
	}
	if (*current && ft_strncmp((*current)->expanded_value, "cat", 3) == 0)
		*cat_cmd = true;
	return (true);
}

char	*handle_redirection2(t_data *data, t_token **current, bool *cat_cmd)
{
	char	*cmd;

	cmd = NULL;
	if (is_first_after_pipe(*current) && (*current)->type != T_PIPE)
	{
		cmd = ms_strdup(data, (*current)->expanded_value);
		(*current) = (*current)->next;
	}
	if ((*current) && is_redir_except_heredoc(*current)  && (*current)->type != T_PIPE)
	{
		if (*cat_cmd)
		{
			cmd = ms_strjoin_with_free_1st(data, cmd, " ");
			cmd = ms_strjoin_with_free_1st(data, cmd, (*current)->next->expanded_value);
			*cat_cmd = false;
		}
		(*current) = (*current)->next->next;
	}
	return (cmd);
}

bool	handle_command(t_data *data, t_token **current, char **cmds, int *j)
{
	while ((*current) && (*current)->type != T_PIPE && !is_redir(*current))
	{
		cmds[*j] = ms_strjoin_with_free_1st(data, cmds[*j], " ");
		cmds[*j] = ms_strjoin_with_free_1st(data, cmds[*j], (*current)->expanded_value);
		(*current) = (*current)->next;
	}
	return (true);
}

bool	handle_loop(t_data *data, t_token **current, char **cmds, int *j)
{
	bool	cat_cmd;
	char	*cmd;
	bool	no_cmd;

	cat_cmd = false;
	cmd = NULL;
	no_cmd = false;
	if (is_heredoc(*current))
		handle_heredoc(data, current, cmds, j);
	while ((*current) && (*current)->type != T_PIPE)
	{
		if (!handle_redirection(current, &cat_cmd, &no_cmd))
			return (false);
		if (no_cmd)
		{
			cmds[*j] = ms_strdup(data, "");
			return (true);
		}
		cmd = handle_redirection2(data, current, &cat_cmd);
		if (cmd)
			cmds[*j] = cmd;
		if (!handle_command(data, current, cmds, j))
			return (free_and_null(&cmd), false);
		if (is_redir(*current) && cmds[*j])
			break ;
	}
	return (true);
}
