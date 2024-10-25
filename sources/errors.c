/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/23 22:55:51 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/10/25 13:20:20 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_error(t_error code)
{
	static char *str[] = {[NO_ERROR] = "No Error\n",
							[ERROR_PERM] = "bash: permission denied: \n",
							// >>   test.txt returns this but bash does nothing,
							//		with 0 exit_code
							[ERROR_ARGUMENT_COUNT] = "please type => ./minishell\n",
							[ERROR_NO_ENVP] = "Error: no envp\n",
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
							[ERROR_META] = "Error: wrong meta character\n",
							[ERROR_SYNTAX] = "bash: syntax error near unexpected token: \n",
							[ERROR_EMPTY_LINE] = "Error: empty line\n",
							[ERROR_INVALID_IDENTIFIER] = "Error: invalid identifier\n",
							[UNDEFINED_ERROR] = "Undefined Error\n"};
	if (code < 0 || code >= UNDEFINED_ERROR)
		return (str[UNDEFINED_ERROR]);
	else
		return (str[code]);
}

// keep program running but print error message from code
void	free_system_error(t_data *data, t_error code)
{
	printf("Free system error\n");
	data->exit_code = code;
	ft_putstr_fd(ft_error(code), STDERR_FILENO);
	free_system(data);
}

// keep program running but print customized error message
void	free_system_perror(t_data *data, t_error code, char *s)
{
	printf("Free system perror\n");
	data->exit_code = code;
	perror(s);
	free_system(data);
}

// only called in main.c
// exit program with error message from code
void	ft_exit_perror(t_error code, char *s)
{
	perror(s);
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

int	ft_print_error(t_error code)
{
	ft_printf_fd(STDERR_FILENO, "%s\n", ft_error(code));
	return (code);
}

void	ft_system_error(t_data *data, t_error code)
{
	data->exit_code = code;
	free_system(data);
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

void	free_and_null(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return ;
}

void	free_2d_null(char ***ptr)
{
	int i;
	char **array;

	if (*ptr == NULL)
		return ;
	array = *ptr;
	i = 0;
	while (array[i])
	{
		free_and_null(&array[i]);
		i++;
	}
	free(array);
	*ptr = NULL;
	return ;
}


void	close_info(t_info *info)
{
	if (info->infile)
		free_and_null(&info->infile);
	if (info->outfile)
		free_and_null(&info->outfile);
	if (info->limiter)
		free_and_null(&info->limiter);
	if (info->path)
		free_and_null(&info->path);
	// free(info);
	// info = NULL;
	return ;
}

void	free_system(t_data *data)
{
	if (data && data->cmds && data->cmds[0])
		free_2d_null(&data->cmds);
	if (data && data->line && data->line[0])
		free_and_null(&data->line);
	if (data && data->info)
		close_info(data->info);
	if (data && data->tokens)
		free_token_list(&data->tokens);
	return ;
}

void	free_data(t_data **data)
{
	free_system(*data);
	if ((*data)->envp && (*data)->envp[0])
		free_2d_null(&(*data)->envp);
	if ((*data)->path)
		free((*data)->path);
	if ((*data)->env_list)
		free_env(&(*data)->env_list);
	free(*data);
	*data = NULL;
	return ;
}

void	free_env(t_env **env_var)
// Not sure of elsewhere already! Need to check !
{
	t_env *current;
	t_env *next;

	current = *env_var;
	while (current != NULL)
	{
		next = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*env_var = NULL;
}

void	ft_putstr2_fd(char *s1, char *s2, int fd)
{
	ft_putstr_fd(s1, fd);
	ft_putstr_fd(s2, fd);
}

void	ft_putstr3_fd(char *s1, char *s2, char *s3, int fd)
{
	ft_putstr_fd(s1, fd);
	ft_putstr_fd(s2, fd);
	ft_putstr_fd(s3, fd);
}
