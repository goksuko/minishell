/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/23 22:55:51 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/09/26 12:09:27 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_error(t_error code)
{
	static char	*str[] = {[NO_ERROR] = "No Error\n",
	[ERROR_PERM] = "bash: permission denied: \n",
	[ERROR_ARGUMENT_COUNT] = "please type => ./minishell\n",
	[ERROR_TOO_MAY_ARGS] = "bash: exit: too many arguments\n",
	[ERROR_NUMERIC_ARG] = "bash: exit: numeric argument required\n",
	[ERROR_ALLOCATION] = "Allocation Failure\n",
	[ERROR_NULL_PATH] = "bash: path not found\n",
	[ERROR_CMD_NOT_FOUND] = "bash: command not found: \n",
	[ERROR_WRONG_CHAR] = "Error: wrong character\n",
	[ERROR_FILE_NOT_FOUND] = "bash: file not found: \n",
	[ERROR_NOT_DIR] = "bash: not a directory: \n",
	[ERROR_QUOTE] = "Error: unclosed quote\n",
	[ERROR_META] = "Error: wrong meta character", // to be erased perhaps...need to review error codes
	[ERROR_SYNTAX] = "bash: syntax error near unexpected token: \n",
	[ERROR_EMPTY_LINE] = "Error: empty line\n",
	[ERROR_INVALID_IDENTIFIER] = "??????",
	[UNDEFINED_ERROR] = "Undefined Error\n"};

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
	free_system(data); // to be replaced with free_shell_data	
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
	free_system(data); // to be replaced with free_shell_data
	exit(code);
}

void	ft_close_exit_perror(t_pipex *info, char **matrix, t_error code,
		char *s)
{
	close_pipex(info, matrix);
	free_system(info->data); // to be replaced with free_shell_data
	perror(s);
	exit(code);
}

void	free_system(t_data *data)
{
	ft_printf("free_system\n");	
	// if (data->line && data->line[0] != '\0')
	// 	free(data->line);
	if (data->cmds && data->cmds[0] != NULL)
		free_matrix(data->cmds);
	if (data->info && data->cmds[0] != NULL)
		free(data->info);
	return ;
}

void	free_shell_data(t_data **data) // to be adjusted
{
	ft_printf("free_shell_data\n");
	if ((*data)->line && (*data)->line[0] != '\0')
		free((*data)->line);
	if ((*data)->tokens)
		free_token_list(&(*data)->tokens);
	close_pipex((*data)->info, (*data)->info->cmds); // Correct??
	// if ((*data)->cmds && (*data)->cmds[0] != NULL)
	// 	free_matrix((*data)->cmds);
	if ((*data)->info && (*data)->cmds[0] != NULL)
		free((*data)->info);
	if ((*data)->path)
		free((*data)->path);
	// if ((*data)->cmds_for_pipe)
	// 	free_matrix((*data)->cmds_for_pipe);
	return ;
}