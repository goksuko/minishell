/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/23 22:55:51 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/07/01 00:02:56 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_error(t_error code)
{
	static char	*str[] = {[NO_ERROR] = "No Error",
			[ERROR_PERM] = "zsh: permission denied: \n",
			[ERROR_ARGUMENT_COUNT] = "please provide: ./minishell file1 cmd1 cmd2 ... cmdn file2\n",
			[ERROR_ALLOCATION] = "Allocation Failure",
			[ERROR_NULL_PATH]	= "zsh: path not found\n",
			[UNDEFINED_ERROR] = "Undefined Error",
			[ERROR_NOT_DIR] = "zsh: not a directory: \n"};

	if (code < 0 || code >= UNDEFINED_ERROR)
		return (str[UNDEFINED_ERROR]);
	else
		return (str[code]);
}

// ft_print_error(ERROR_ARGUMENT_COUNT);
int		ft_print_error(t_error code)
{
	ft_printf("%s\n", ft_error(code));
	return (code);
}

// ft_exit_perror(ERROR_MUTEX_INIT, "Dead Lock in Table Init");
void	ft_exit_perror(t_error code, char *s)
{
	perror(s);
	exit(code);
}

// ft_exit_str_fd(ERROR_MUTEX_INIT, STDERR_FILENO);
void	ft_exit_str_fd(t_error code, int fd)
{
	ft_putstr_fd(ft_error(code), fd);
	exit(code);
}

void	ft_close_exit_perror(t_pipex *info, char **matrix, t_error code, char *s)
{
	close_pipex(info, matrix);
	free(info);
	perror(s);
	exit(code);
}
