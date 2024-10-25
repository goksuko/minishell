/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 13:46:35 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/25 13:46:35 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(char **cmds, t_data *data)
{
	char	*cwd;
	int		out_fd;

	if (data->info->fd_out == -10)
		out_fd = STDOUT_FILENO;
	else
		out_fd = data->info->fd_out;
	cwd = NULL;
	if (errno == ENOMEM || cmds[0] != NULL)
	{
		free_system_error(data, ERROR_TOO_MANY_ARGS);
		return (ERROR_TOO_MANY_ARGS);
	}
	cwd = getcwd(cwd, 0);
	if (errno == ENOMEM || cwd == NULL)
	{
		free_system_perror(data, ERROR_ALLOCATION, "cwd in ft_pwd");
		return (ERROR_ALLOCATION);
	}
	ft_putendl_fd(cwd, out_fd);
	free(cwd);
	return (SUCCESS);
}
