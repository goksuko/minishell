/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/18 23:18:03 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/18 11:28:05 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_path(t_info *info, char *main_command)
{
	char	*path;
	char	**path_split;
	char	*temp;
	int		i;

	if (access(main_command, F_OK | X_OK) == 0)
		return (main_command);
	path_split = ft_split(info->data->path, ':');
	if (errno == ENOMEM || path_split == NULL)
		ft_exit_data_perror(info->data, ERROR_ALLOCATION, "path_split in find_path");
	i = 0;
	while (path_split[i])
	{
		if (is_file(path_split[i]))
		{
			if (info-> infile == NULL)
				info->infile = path_split[i];

		}
		temp = ft_strjoin(path_split[i], "/");
		if (errno == ENOMEM || temp == NULL)
		{
			ft_free_matrix(path_split);
			ft_exit_data_perror(info->data, ERROR_ALLOCATION, "temp in find_path");
		}
		path = ft_strjoin(temp, main_command);
		if (errno == ENOMEM || path == NULL)
		{
			free(temp);
			ft_free_matrix(path_split);
			ft_exit_data_perror(info->data, ERROR_ALLOCATION, "path in find_path");
		}
		free(temp);
		if (access(path, F_OK | X_OK) == 0)
			return (ft_free_matrix(path_split), path);
		free(path);
		i++;
	}
	ft_free_matrix(path_split);
	return (NULL);
}
