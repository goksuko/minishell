/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   messages.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/18 12:20:50 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/11/24 21:34:04 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	a_directory(t_data *data, char *str)
{
	ft_putstr3_fd(str, ": Is a directory", "\n", STDERR_FILENO);
	data->exit_code = 126;
	return ;
}

void	permission_denied(t_data *data, char *str)
{
	ft_putstr3_fd(str, ": Permission denied", "\n", STDERR_FILENO);
	data->exit_code = 126;
	return ;
}

void	not_found(t_data *data, char *str)
{
	ft_putstr3_fd(str, ": No such file or directory", "\n", STDERR_FILENO);
	data->exit_code = 127;
	return ;
}

void	comm_not_found(t_data *data, char *str)
{
	if (str)
		ft_putstr3_fd(str, ": command not found", "\n", STDERR_FILENO);
	data->exit_code = 127;
	return ;
}

void	all_messages(t_data *data, char *str)
{
	if (str && str[0] == '/')
		not_found(data, str);
	else if (str && str[0] == '.' && str[1] == '/')
	{
		if (access(str, F_OK))
		{
			if (access(str, X_OK) != 0)
				permission_denied(data, str);
			else
				not_found(data, str);
		}
		else
		{
			if (is_directory(str))
				a_directory(data, str);
			else
				permission_denied(data, str);
		}
	}
	else
		comm_not_found(data, str);
	return ;
}
