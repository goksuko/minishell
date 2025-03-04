/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_stuff.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/04 14:35:10 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/11/25 10:20:35 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_and_null(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_2d_null(char ***ptr)
{
	int		i;
	char	**array;

	if (*ptr == NULL)
		return ;
	array = *ptr;
	i = 0;
	while (array[i])
	{
		free_and_null(&array[i]);
		i++;
	}
	free(array);
	*ptr = NULL;
	return ;
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
}

void	free_system(t_data *data)
{
	if (data && data->cmds)
		free_2d_null(&data->cmds);
	if (data && data->line && data->line[0])
		free_and_null(&data->line);
	if (data && data->info)
		free_info(data->info);
	if (data && data->tokens)
		free_token_list(&data->tokens);
	if (data && data->path)
		free_and_null(&data->path);
	return ;
}

void	free_data(t_data **data)
{
	free_system(*data);
	if ((*data) && (*data)->envp && (*data)->envp[0])
		free_2d_null(&(*data)->envp);
	if ((*data) && (*data)->env_list)
		free_env(&(*data)->env_list);
	close_fds(*data, (*data)->info);
	rl_clear_history();
	free(*data);
	*data = NULL;
	return ;
}
