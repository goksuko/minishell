/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/18 23:18:03 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/07/05 22:59:33 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// envp = environment variables of the process
int	find_path_index(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (0);
}

char	*find_path(char *main_command, char **envp)
{
	char	*path;
	char	**path_split;
	int		i;
	char	*tmp;

	i = 0;
	if (access(main_command, F_OK | X_OK) == 0)
		return (main_command);
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	path_split = ft_split(envp[i] + 5, ':');
	if (errno == ENOMEM || path_split == NULL)
		ft_exit_perror(ERROR_ALLOCATION, "path_split in find_path");
	i = 0;
	while (path_split[i])
	{
		tmp = ft_strjoin(path_split[i], "/");
		if (errno == ENOMEM || tmp == NULL)
			ft_exit_perror(ERROR_ALLOCATION, "tmp in find_path");
		path = ft_strjoin(tmp, main_command);
		if (errno == ENOMEM || path == NULL)
			ft_exit_perror(ERROR_ALLOCATION, "path in find_path");
		free(tmp);
		if (access(path, F_OK | X_OK) == 0)
			return (free_matrix(path_split), path);
		free(path);
		i++;
	}
	free_matrix(path_split);
	return (NULL);
}
// strjoin controls recently added so that it has more than 25 lines

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
