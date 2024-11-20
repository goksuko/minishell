/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds_between_pipes.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 22:34:41 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/11/20 14:25:56 by akaya-oz      ########   odam.nl         */
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

// bool	handle_later_heredoc(t_data *data, t_token **current, char **cmds, int *j)
// {
// 	cmds[*j] = ms_strdup(data, (*current)->expanded_value);
// 	(*current) = (*current)->next;
// 	while ((*current) && (*current)->type != T_DSMALLER)
// 	{
// 		cmds[*j] = ms_strjoin(data, cmds[*j], " ");
// 		cmds[*j] = ms_strjoin(data, cmds[*j], (*current)->expanded_value);
// 		(*current) = (*current)->next;
// 	}
// 	while ((*current) && (*current)->type != T_PIPE)
// 		(*current) = (*current)->next;
// 	return (true);
// }

bool	handle_redirection(t_token **current, bool *cat_cmd, bool *no_cmd)
{
	if (is_redir_except_heredoc(*current) && is_first_after_pipe(*current))
	{
		// printf("here2\n");
		// printf("current: %s\n", (*current)->expanded_value);
		if ((*current)->next->next == NULL)
		{
			// printf("here3\n");
			*no_cmd = true;
			// return (true);
		}
		if ((*current)->next->next->type == T_PIPE)
		{
			// printf("here\n");
			*no_cmd = true;
			// *current = (*current)->next->next;
			// return (true);
		}
		// else
		// {
			*current = redir_first(*current);
			if (!*current)
				return (false);
		// }
	}
	if (*current && ft_strncmp((*current)->expanded_value, "cat", 3) == 0)
		*cat_cmd = true;
	// printf("to return true\n");
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
	char	*temp;

	while ((*current) && (*current)->type != T_PIPE && !is_redir(*current))
	{
		temp = cmds[*j];
		cmds[*j] = ms_strjoin(data, cmds[*j], " ");
		free(temp);
		temp = cmds[*j];
		cmds[*j] = ms_strjoin(data, cmds[*j], (*current)->expanded_value);
		free(temp);
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
	// if (is_redir_inside(*current))
	// 	handle_later_heredoc(data, current, cmds, j);
	// if (*current)
	// 	printf("0: %s\n", (*current)->expanded_value);
	while ((*current) && (*current)->type != T_PIPE)
	{
		// if (*current)
		// 	printf("1: %s\n", (*current)->expanded_value);
		if (!handle_redirection(current, &cat_cmd, &no_cmd))
		// {
			// printf("returned false\n");
			return (false);
		// }
		// if (no_cmd)
		// {
		// 	cmds[*j] = NULL;
		// 	// (*j)++;
		// 	return (true);
		// }
		// else
		// {
			// if (*current)
			// 	printf("2: %s\n", (*current)->expanded_value);
			// if (!*current || (*current)->type == T_PIPE)
				// break ;
			cmd = handle_redirection2(data, current, &cat_cmd);
			if (cmd)
				cmds[*j] = cmd;
			// else
			// 	printf("cmd is null\n");
			// if (*current)
			// 	printf("3: %s\n", (*current)->expanded_value);
			if (!handle_command(data, current, cmds, j))
				return (free_and_null(&cmd), false);
			// if (*current)
			// 	printf("4: %s\n", (*current)->expanded_value);
			if (is_redir(*current) && cmds[*j])
				break ;
			// if (*current)
			// 	printf("5: %s\n", (*current)->expanded_value);			
		// }
	}
	// printf("handle loop returning true\n");
	return (true);
}
