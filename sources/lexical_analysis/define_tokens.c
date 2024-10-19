/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   define_tokens.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/17 11:22:02 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/19 13:01:30 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	define_token_fd(t_data *data, t_token *token)
{
	if (token->type == T_SMALLER)
	{
		if (define_smaller(data, token) == false)
			return (false);
	}
	else if (token->type == T_GREATER)
	{
		if (define_greater(data, token) == false)
			return (false);
	}
	else if (token->type == T_DSMALLER)
	{
		if (define_dsmaller(data, token) == false)
			return (false);
	}
	else if (token->type == T_DGREATER)
	{
		if (define_dgreater(data, token) == false)
			return (false);
	}
	return (true);
}

bool	define_smaller(t_data *data, t_token *token)
{
	int	temp_fd;

	temp_fd = open(token->next->value, O_RDONLY, 0777);
	if (temp_fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "bash: %s: Permission denied\n",
			token->next->value);
		data->exit_code = ERROR_NO_FILE_DIR;
		free_system(data);
		return (false);
	}
	token->next->fd_in = temp_fd;
	// printf("< fd_in: %d, infile: %s\n", temp_fd, token->next->value);
	return (true);
}

bool	define_greater(t_data *data, t_token *token)
{
	int	temp_fd;

	temp_fd = open(token->next->value, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (temp_fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "bash: %s: Permission denied\n",
			token->next->value);
		data->exit_code = ERROR_NO_FILE_DIR;
		free_system(data);
		return (false);
	}
	token->next->fd_out = temp_fd;
	// printf("> fd_out: %d, outfile: %s\n", temp_fd, token->next->value);
	return (true);
}

bool	define_dsmaller(t_data *data, t_token *token)
{
	int	temp_fd;

	temp_fd = open("0ur_h3r3_d0c", O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (temp_fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "bash: %s: Permission denied\n",
			token->next->value);
		data->exit_code = ERROR_NO_FILE_DIR;
		free_system(data);
		return (false);
	}
	token->next->here_doc_fd = temp_fd;
	token->next->limiter = ft_strdup(token->next->value);
	if (token->next->limiter == NULL)
	{
		free_system_perror(data, ERROR_ALLOCATION,
			"limiter in define_dsmaller");
		return (false);
	}
	// printf("<< here_doc_fd: %d, limiter: %s\n", token->next->here_doc_fd,
	//		token->next->limiter);
	return (true);
}

bool	define_dgreater(t_data *data, t_token *token)
{
	int	temp_fd;

	temp_fd = open(token->next->value, O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (temp_fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "bash: %s: Permission denied\n",
			token->next->value);
		data->exit_code = ERROR_NO_FILE_DIR;
		free_system(data);
		return (false);
	}
	token->next->fd_out = temp_fd;
	// printf(">> fd_out: %d, outfile: %s\n", temp_fd, token->next->value);
	return (true);
}
