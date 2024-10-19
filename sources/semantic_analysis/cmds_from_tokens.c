/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds_from_tokens.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 22:31:33 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/19 22:44:29 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*redir_first(t_token *current)
{
	t_token	*temp;
	t_token	*smaller;
	t_token	*file;
	t_token	*next_token;

	if (current->next == NULL || current->next->next == NULL)
		return (NULL);
	smaller = current;
	file = current->next;
	temp = current->next->next;
	next_token = temp->next;
	temp->next = smaller;
	temp->prev = NULL;
	smaller->prev = temp;
	file->next = next_token;
	return (temp);
}

char	*do_cat_addition(t_token *current, char *cmd)
{
	cmd = ft_strjoin(cmd, " ");
	if (cmd == NULL)
		return (NULL);
	cmd = ft_strjoin(cmd, current->next->expanded_value);
	if (cmd == NULL)
		return (NULL);
	return (cmd);
}

bool	is_first_after_pipe(t_token *current)
{
	if (current && (current->prev == NULL || current->prev->type == T_PIPE))
		return (true);
	return (false);
}

char	**cmds_between_pipes(t_data *data, char **cmds)
{
	int		j;
	t_token	*current;
	bool	cat_cmd;

	cat_cmd = false;
	j = 0;
	current = data->tokens;
	while (current && current->type != T_PIPE)
	{
		if (handle_loop(&current, cmds, &j, &cat_cmd) == false)
			return (NULL);
		if (current && current->type == T_PIPE)
			current = current->next;
		j++;
	}
	cmds[j] = NULL;
	return (cmds);
}

char	**cmds_from_tokens(t_data *data)
{
	char	**cmds;

	cmds = (char **)ft_calloc(sizeof(char *), (data->nbr_of_pipes + 2));
	if (errno == ENOMEM || cmds == NULL)
	{
		free_system_perror(data, ERROR_ALLOCATION, "cmds in cmds_from_tokens");
		return (NULL);
	}
	cmds = cmds_between_pipes(data, cmds);
	if (cmds == NULL)
	{
		free_system_perror(data, ERROR_ALLOCATION, "cmds in cmds_from_tokens");
		return (NULL);
	}
	return (cmds);
}
