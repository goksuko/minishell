/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/04 14:29:21 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/11/04 14:29:21 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// keep program running but print error message from code
void	free_system_error(t_data *data, t_error code)
{
	data->exit_code = code;
	ft_putstr_fd(ft_error(code), STDERR_FILENO);
	free_system(data);
}

// keep program running but print customized error message
void	free_system_perror(t_data *data, t_error code, char *s)
{
	data->exit_code = code;
	perror(s);
	free_system(data);
}

// exit program with exit_code, clean if data is present,
// and writes error message from errno
void	ft_exit_perror(t_data *data, t_error code)
{
	perror(NULL);
	free_data(&data);
	exit(code);
}

// exit program with error message from code and frees data
void	ft_exit_data_error(t_data *data, t_error code)
{
	ft_printf_fd(STDERR_FILENO, "%s\n", ft_error(code));
	free_data(&data);
	exit(code);
}

// exit program with customized error message and frees data
void	ft_exit_data_perror(t_data *data, t_error code, char *s)
{
	perror(s);
	free_data(&data);
	exit(code);
}
