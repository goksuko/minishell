/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/19 23:08:50 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/19 23:08:51 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	cat_inside(t_token *current)
{
	if (current && ft_strncmp(current->value, "cat", 3) == 0)
		return (true);
	return (false);
}

int	last_exit_code_checks(int exit_code, t_data *data)
{
	if (exit_code == 1 && cat_inside(data->tokens))
		return (0);
	if (WIFSIGNALED(exit_code))
	{
		if (WTERMSIG(exit_code) == 2)
			return (130);
		if (WTERMSIG(exit_code) == 3)
			return (131);
	}
	return (exit_code);
}

bool	execute_shell(t_data *data)
{
	int	exit_code;

	data->nbr_of_pipes = find_pipe_count(data->tokens);
	data->exit_code = 0;
	data->info->pipe_read_end = STDIN_FILENO;
	data->info->here_doc_cmd = heredoc_position(data->tokens);
	if (create_children(data) == false)
		return (false);
	if (data->info->limiter)
	{
		if (unlink("0ur_h3r3_d0c") < 0)
			return (false);
	}
	exit_code = data->exit_code;
	data->exit_code = last_exit_code_checks(exit_code, data); // to be checked
	// free_system(data);
	return (true);
}

int	is_file(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (false);
	return (S_ISREG(path_stat.st_mode));
}
