/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/23 22:55:51 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/11/25 10:12:00 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_error(t_error code)
{
	static char	*str[] = {[NO_ERROR] = "No Error\n",
	[ERROR_PERM] = "bash: permission denied: \n",
	[ERROR_ARGUMENT_COUNT] = "please type => ./minishell\n",
	[ERROR_NO_ENVP] = "Error: no envp\n",
	[ERROR_TOO_MANY_ARGS] = "bash: exit: too many arguments\n",
	[ERROR_NUMERIC_ARG] = "bash: exit: numeric argument required\n",
	[ERROR_ALLOCATION] = "Allocation Failure\n",
	[ERROR_NULL_PATH] = "bash: path not found\n",
	[ERROR_WRONG_CHAR] = "Error: wrong character\n",
	[ERROR_FILE_NOT_FOUND] = "bash: file not found: \n",
	[ERROR_PIPE] = "bash: pipe error: \n",
	[ERROR_FORK] = "bash: fork error: \n",
	[ERROR_DUP2] = "bash: dup2 error: \n",
	[ERROR_UNLINK] = "bash: unlink error: \n",
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

void	ft_system_error(t_data *data, t_error code)
{
	data->exit_code = code;
	free_system(data);
}

void	free_info(t_info *info)
{
	if (info->infile)
		free_and_null(&info->infile);
	if (info->outfile)
		free_and_null(&info->outfile);
	if (info->limiter)
		free_and_null(&info->limiter);
	if (info->path)
		free_and_null(&info->path);
	return ;
}

void	free_env(t_env **env_var)
{
	t_env	*current;
	t_env	*next;

	current = *env_var;
	while (current != NULL)
	{
		next = current->next;
		if (current->key)
			free_and_null(&current->key);
		if (current->value)
			free_and_null(&current->value);
		free(current);
		current = next;
	}
	*env_var = NULL;
}

int	error_assign(t_data *data, t_error code)
{
	data->exit_code = code;
	return (code);
}
