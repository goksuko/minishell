/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   define_tokens.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/17 11:22:02 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/17 11:22:02 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	define_token_fd(t_data *data, t_token *token)
{
	if (token->type == T_SMALLER)
		define_smaller(data, token);
	else if (token->type == T_GREATER)
		define_greater(data, token);
	else if (token->type == T_DSMALLER)
		define_dsmaller(data, token);
	else if (token->type == T_DGREATER)
		define_dgreater(data, token);
}

void	define_smaller(t_data *data, t_token *token)
{
	int	temp_fd;

	temp_fd = open(token->next->value, O_RDONLY, 0777);
	if (temp_fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "bash: %s: Permission denied\n", \
		token->next->value);
		data->exit_code = 1;
		free_data(&data);
		exit(1);
	}
	token->next->fd_in = temp_fd;
	printf("< fd_in: %d, infile: %s\n", temp_fd, token->next->value);
}

void	define_greater(t_data *data, t_token *token)
{
	int	temp_fd;

	temp_fd = open(token->next->value, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (temp_fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "bash: %s: Permission denied\n", \
		token->next->value);
		data->exit_code = 1;
		free_data(&data);
		exit(1);
	}
	token->next->fd_out = temp_fd;
	printf("> fd_out: %d, outfile: %s\n", temp_fd, token->next->value);
}

void	define_dsmaller(t_data *data, t_token *token)
{
	int	temp_fd;

	temp_fd = open("0ur_h3r3_d0c", O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (temp_fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "bash: %s: Permission denied\n", \
		token->next->value);
		data->exit_code = 1;
		free_data(&data);
		exit(1);
	}
	token->next->here_doc_fd = temp_fd;
	token->next->limiter = ft_strdup(token->next->value);
	printf("<< here_doc_fd: %d, limiter: %s\n", token->next->here_doc_fd, \
	token->next->limiter);
}

void	define_dgreater(t_data *data, t_token *token)
{
	int	temp_fd;

	temp_fd = open(token->next->value, O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (temp_fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "bash: %s: Permission denied\n", \
		token->next->value);
		data->exit_code = 1;
		free_data(&data);
		exit(1);
	}
	token->next->fd_out = temp_fd;
	printf(">> fd_out: %d, outfile: %s\n", temp_fd, token->next->value);
}
