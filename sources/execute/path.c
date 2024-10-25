/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/18 23:18:03 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/25 13:21:32 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_path_helper(t_info *info, char *main_command, char **path_split,
		int i)
{
	char	*path;
	char	*temp;

	if (is_file(path_split[i]))
	{
		if (info->infile == NULL)
			info->infile = path_split[i];
	}
	temp = ft_strjoin(path_split[i], "/");
	if (temp == NULL)
		return (NULL);
	path = ft_strjoin(temp, main_command);
	if (path == NULL)
		return (NULL);
	free(temp);
	if (access(path, F_OK | X_OK) == 0)
		return (free_2d_null(&path_split), path);
	free(path);
	return (NULL);
}

char	*find_path(t_info *info, char *main_command)
{
	char	*path;
	char	**path_split;
	int		i;

	if (access(main_command, F_OK | X_OK) == 0)
		return (main_command);
	path_split = ft_split(info->data->path, ':');
	if (errno == ENOMEM || path_split == NULL)
		ft_exit_data_perror(info->data, ERROR_ALLOCATION,
			"path_split in find_path");
	i = 0;
	while (path_split[i])
	{
		path = find_path_helper(info, main_command, path_split, i);
		if (path)
			return (path);
		i++;
	}
	free_2d_null(&path_split);
	return (NULL);
}
