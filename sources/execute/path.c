/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/18 23:18:03 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/14 15:11:33 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


// path_from_getenv  
// is a list of directories separated by colons (`:`) 
// on Unix-like systems (Linux, macOS) or semicolons (`;`) on Windows. 
// This list is what the shell and other programs use 
// to find executables when a command is issued.

char	*find_path(t_info *info, char *main_command, char *path_from_getenv)
{
	char	*path;
	char	**path_split;
	char	*temp;
	int		i;

	// printf("main_command: %s\n", main_command);
	if (access(main_command, F_OK | X_OK) == 0)
		return (main_command);
	// printf("main_command was not accessible\n");
	path_split = ft_split(path_from_getenv, ':');
	if (errno == ENOMEM || path_split == NULL)
		ft_exit_data_perror(info->data, ERROR_ALLOCATION, "path_split in find_path");
	i = 0;
	while (path_split[i])
	{
		// printf("path_split[%d]: %s\n", i, path_split[i]);
		if (is_file(path_split[i]))
		{
			if (info-> infile == NULL)
				info->infile = path_split[i];
			else if (info->outfile != NULL) //check if this is correct
				info->outfile = path_split[i];
		}
		temp = ft_strjoin(path_split[i], "/");
		// printf("temp: %s\n", temp);
		if (errno == ENOMEM || temp == NULL)
		{
			free_matrix(path_split);
			ft_exit_data_perror(info->data, ERROR_ALLOCATION, "temp in find_path");
		}
		path = ft_strjoin(temp, main_command);
		// printf("path: %s\n", path);
		if (errno == ENOMEM || path == NULL)
		{
			free(temp);
			free_matrix(path_split);
			ft_exit_data_perror(info->data, ERROR_ALLOCATION, "path in find_path");
		}
		free(temp);
		if (access(path, F_OK | X_OK) == 0)
			return (free_matrix(path_split), path);
		free(path);
		i++;
	}
	free_matrix(path_split);
	return (NULL);
}

// int	command_not_found(char *cmds[])
// {
// 	char	*cmd_1;
// 	char	*cmd_2;

// 	cmd_1 = put_main_command(argv[2], ' ');
// 	cmd_2 = put_main_command(argv[3], ' ');
// 	ft_putstr2_fd("zsh: command not found: ", cmd_1, STDERR_FILENO);
// 	ft_putstr3_fd("\nzsh: command not found: ", cmd_2, "\n", STDERR_FILENO);
// 	free(cmd_1);
// 	free(cmd_2);
// 	return (127);
// }