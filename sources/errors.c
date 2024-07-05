/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/23 22:55:51 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/07/05 23:02:38 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_error(t_error code)
{
	static char	*str[] = {[NO_ERROR] = "No Error",
	[ERROR_PERM] = "zsh: permission denied: \n",
	[ERROR_ARGUMENT_COUNT] = "please type => ./minishell\n",
	[ERROR_ALLOCATION] = "Allocation Failure",
	[ERROR_NULL_PATH] = "zsh: path not found\n",
	[ERROR_CMD_NOT_FOUND] = "zsh: command not found: \n",
	[ERROR_WRONG_CHAR] = "Error: wrong character\n",
	[ERROR_QUOTE] = "Error: unclosed quote\n",
	[UNDEFINED_ERROR] = "Undefined Error",
	[ERROR_NOT_DIR] = "zsh: not a directory: \n"};

	if (code < 0 || code >= UNDEFINED_ERROR)
		return (str[UNDEFINED_ERROR]);
	else
		return (str[code]);
}

// ft_print_error(ERROR_ARGUMENT_COUNT);
int	ft_print_error(t_error code)
{
	ft_printf_fd(STDERR_FILENO, "%s\n", ft_error(code));
	return (code);
}

// ft_exit_perror(ERROR_MUTEX_INIT, "Dead Lock in Table Init");
void	ft_exit_perror(t_error code, char *s)
{
	perror(s);
	exit(code);
}

void	ft_exit_data_perror(t_data *data, t_error code, char *s)
{
	perror(s);
	free_system(data);
	exit(code);
}

// ft_exit_str_fd(ERROR_MUTEX_INIT, STDERR_FILENO);
void	ft_exit_str_fd(t_error code, int fd)
{
	ft_putstr_fd(ft_error(code), fd);
	exit(code);
}

void	ft_exit_str_free_fd(t_error code, char *str, int fd)
{
	ft_putstr_fd(ft_error(code), fd);
	free(str);
	exit(code);
}

void	ft_exit_data_error(t_data *data, t_error code)
{
	ft_printf_fd(STDERR_FILENO, "%s\n", ft_error(code));
	free_system(data);
	exit(code);
}

void	ft_close_exit_perror(t_pipex *info, char **matrix, t_error code,
		char *s)
{
	close_pipex(info, matrix);
	free_system(info->data);
	perror(s);
	exit(code);
}

void	free_system(t_data *data)
{
	// if (data->line && data->line[0] != '\0')
	// 	free(data->line);
	if (data->cmds && data->cmds[0] != NULL)
		free_matrix(data->cmds);
	if (data->info && data->info->cmds[0] != NULL)
		free(data->info);
	return ;
}
