/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds_from_tokens.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 22:31:33 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/11/09 22:13:32 by akaya-oz      ########   odam.nl         */
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

// char	*do_cat_addition(t_data *data, t_token *current, char *cmd)
// {
// 	cmd = ms_strjoin(data, cmd, " ");
// 	cmd = ms_strjoin(data, cmd, current->next->expanded_value);
// 	return (cmd);
// }

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

	j = 0;
	current = data->tokens;
	while (current && current->type != T_PIPE)
	{
		if (handle_loop(data, &current, cmds, &j) == false)
		{
			free_2d_null(&cmds);
			return	(NULL);
		}
			// return (NULL);
		while (current && current->type != T_PIPE) //for skipping redirections
			current = current->next;
		if (current && current->type == T_PIPE)
			current = current->next;
		j++;
	}
	cmds[j] = NULL;
	// printf_array(cmds);
	return (cmds);
}

char	**cmds_from_tokens(t_data *data)
{
	char	**cmds;

	cmds = (char **)ms_calloc(data, sizeof(char *), (data->nbr_of_pipes + 2));
	cmds = cmds_between_pipes(data, cmds);
	printf("size of cmds matrix in data struct: %lu\n", sizeof(data->cmds));
	return (cmds);
}
