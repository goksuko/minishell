/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds_between_pipes.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 22:34:41 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/27 11:46:32 by akaya-oz      ########   odam.nl         */
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

bool	handle_redirection(t_token **current, bool *cat_cmd)
{
	printf("handle_redirection\n");
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

char	*handle_redirection2(t_data *data, t_token **current, bool *cat_cmd)
{
	char	*cmd;

	cmd = NULL;
	printf("handle_redirection2\n");
	if (is_first_after_pipe(*current))
	{
		cmd = ms_strdup(data, (*current)->expanded_value);
		(*current) = (*current)->next;
	}
	if ((*current) && is_redir_except_heredoc(*current))
	{
		if (*cat_cmd)
		{
			printf("cat\n");
			// cmds[*j] = do_cat_addition(data, *current, cmds[*j]);
			cmd = ms_strjoin(data, cmd, " ");
			cmd = ms_strjoin(data, cmd, (*current)->next->expanded_value);
			*cat_cmd = false;
		}
		(*current) = (*current)->next->next;
	}
	return (cmd);
}

bool	handle_command(t_data *data, t_token **current, char **cmds, int *j)
{
	printf("handle_command\n");
	while ((*current) && (*current)->type != T_PIPE && !is_redir(*current))
	{
		cmds[*j] = ms_strjoin(data, cmds[*j], " ");
		cmds[*j] = ms_strjoin(data, cmds[*j], (*current)->expanded_value);
		printf("cmds[j] : %s\n", cmds[*j]);
		printf("current->expanded_value : %s\n", (*current)->expanded_value);
		(*current) = (*current)->next;
	}
	return (true);
}

bool	handle_loop(t_data *data, t_token **current, char **cmds, int *j)
{
	bool	cat_cmd;

	cat_cmd = false;
	printf("handle_loop\n");
	while ((*current) && (*current)->type != T_PIPE)
	{
		if (is_heredoc(*current))
		{
			if (!handle_heredoc(data, current, cmds, j))
				return (false);
		}
		if (!handle_redirection(current, &cat_cmd))
			return (false);
		cmds[*j] = ms_strdup(data, handle_redirection2(data, current, &cat_cmd));
		if (!handle_command(data, current, cmds, j))
			return (false);
		// if ((*current))
		// 	printf("cmds[j]: %s, current: %d\n", cmds[*j], (*current)->type);
		if (is_redir(*current) && cmds[*j]) //for skipping redirections
			break ;
	}
	return (true);
}
