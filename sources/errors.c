/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/23 22:55:51 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/13 22:28:17 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_error(t_error code)
{
	static char	*str[] = {[NO_ERROR] = "No Error\n",
	[ERROR_PERM] = "bash: permission denied: \n", // >>   test.txt returns this but bash does nothing, with 0 exit_code
	[ERROR_ARGUMENT_COUNT] = "please type => ./minishell\n",
	[ERROR_TOO_MANY_ARGS] = "bash: exit: too many arguments\n",
	[ERROR_NUMERIC_ARG] = "bash: exit: numeric argument required\n",
	[ERROR_ALLOCATION] = "Allocation Failure\n",
	[ERROR_NULL_PATH] = "bash: path not found\n",
	[ERROR_CMD_NOT_FOUND] = "bash: command not found: \n",
	[ERROR_WRONG_CHAR] = "Error: wrong character\n",
	[ERROR_FILE_NOT_FOUND] = "bash: file not found: \n",
	[ERROR_NOT_DIR] = "bash: not a directory: \n",
	[ERROR_HOME_DIR] = "Error: HOME directory not set\n",
	[ERROR_PARENT_DIR] = "Error: Parent directory not set\n",
	[ERROR_OLDPWD] = "Error: OLDPWD not set\n",
	[ERROR_NO_FILE_DIR] = "Error: No such file or directory\n",
	[ERROR_QUOTE] = "Error: unclosed quote\n",
	[ERROR_META] = "Error: wrong meta character", // to be erased perhaps...need to review error codes
	[ERROR_SYNTAX] = "bash: syntax error near unexpected token: \n",
	[ERROR_EMPTY_LINE] = "Error: empty line\n",
	[ERROR_INVALID_IDENTIFIER] = "Error: invalid identifier\n",
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
	free_data(&data);
	//free_system(data); // to be replaced with free_data	
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
	free_data(&data);
	// free_system(data); // to be replaced with free_data
	exit(code);
}

void	ft_close_exit_perror(t_info *info, t_error code, char *s)
{
	close_info(info);
	free_system(info->data); // to be replaced with free_data
	perror(s);
	exit(code);
}

void	*free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return (NULL);
	while (matrix[i])
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	if (matrix)
	{
		free(matrix);
		matrix = NULL;
	}
	return (NULL);
}

void	close_info(t_info *info)
{
	// printf("close_info\n");
	if (info->infile)
		free(info->infile);
	if (info->outfile)
		free(info->outfile);
	if (info->expanded_cmds)
		free_matrix(info->expanded_cmds);
	if (info->limiter)
		free(info->limiter);
	if (info->path)
		free(info->path);
	if (info->path_from_getenv)
		free(info->path_from_getenv);
	if (info->fd_in != -10)
		close_safe(info->fd_in, info);
	if (info->fd_out != -10)
		close_safe(info->fd_out, info);
	if (info->pipefd[0] != -10)
		close_safe(info->pipefd[0], info);
	if (info->pipefd[1] != -10)
		close_safe(info->pipefd[1], info);
	free(info);
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

void	free_data(t_data **data) // to be adjusted
{
	ft_printf("free_data\n");
	if ((*data)->line && (*data)->line[0] != '\0')
		free((*data)->line);
	if ((*data)->tokens)
		free_token_list(&(*data)->tokens);
	close_info((*data)->info); // Correct??
	// if ((*data)->cmds && (*data)->cmds[0] != NULL)
	// 	free_matrix((*data)->cmds);
	if ((*data)->info && (*data)->cmds[0] != NULL)
		free((*data)->info);
	if ((*data)->path)
		free((*data)->path);
	return ;
}

void	free_env(t_env **env_var) // Not sure of elsewhere already! Need to check ! 
{
	t_env	*current;
	t_env	*next;

	current = *env_var;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	*env_var = NULL;
}