/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/18 23:18:03 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/11/20 23:26:42 by akaya-oz      ########   odam.nl         */
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
			info->infile = ms_strdup(info->data, path_split[i]);
	}
	temp = ms_strjoin(info->data, path_split[i], "/");
	path = ms_strjoin(info->data, temp, main_command);
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
	path_split = ms_split(info->data, info->data->path, ':');
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
