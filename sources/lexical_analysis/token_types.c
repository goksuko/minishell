/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_types.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 14:32:37 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/19 13:02:10 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*token_type_to_string(t_token_type type)
{
	static char	*str[] = {[T_BUILTIN] = "BUILTIN",
	[T_IDENTIFIER] = "IDENTIFIER", [T_SMALLER] = "SMALLER",
	[T_GREATER] = "GREATER", [T_DSMALLER] = "DSMALLER",
	[T_DGREATER] = "DGREATER", [T_PIPE] = "PIPE", [T_FLAG] = "FLAG",
	[T_SINGLE_QUOTES] = "SINGLE_QUOTES",
	[T_DOUBLE_QUOTES] = "DOUBLE_QUOTES", [T_UNKNOWN] = "UNKNOWN"};

	if (type < 0 || type >= sizeof(str) / sizeof(str[0]))
		return (str[T_UNKNOWN]);
	return (str[type]);
}

t_token_type	check_command(char *token)
{
	int	token_len;

	token_len = ft_strlen(token);
	if ((ft_strncmp(token, "echo", 4) == 0 || ft_strncmp(token, "ECHO", 4) == 0)
		&& token_len == 4)
		return (T_BUILTIN);
	if (ft_strncmp(token, "cd", 2) == 0 && token_len == 2)
		return (T_BUILTIN);
	if ((ft_strncmp(token, "pwd", 3) == 0 || ft_strncmp(token, "PWD", 3) == 0)
		&& token_len == 3)
		return (T_BUILTIN);
	if (ft_strncmp(token, "export", 6) == 0 && token_len == 6)
		return (T_BUILTIN);
	if (ft_strncmp(token, "unset", 5) == 0 && token_len == 5)
		return (T_BUILTIN);
	if ((ft_strncmp(token, "env", 3) == 0 || ft_strncmp(token, "ENV", 3) == 0)
		&& token_len == 3)
		return (T_BUILTIN);
	if (ft_strncmp(token, "exit", 4) == 0 && token_len == 4)
		return (T_BUILTIN);
	return (T_UNKNOWN);
}

t_token_type	check_redirection(char *token)
{
	if (ft_strncmp(token, ">>", 2) == 0)
		return (T_DGREATER);
	if (ft_strncmp(token, "<<", 2) == 0)
		return (T_DSMALLER);
	if (ft_strncmp(token, "<", 1) == 0)
		return (T_SMALLER);
	if (ft_strncmp(token, ">", 1) == 0)
		return (T_GREATER);
	return (T_UNKNOWN);
}

t_token_type	check_pipes(char *token)
{
	if (ft_strncmp(token, "|", 1) == 0)
		return (T_PIPE);
	return (T_UNKNOWN);
}

t_token_type	check_flag(char *token)
{
	if (ft_strncmp(token, "-", 1) == 0)
		return (T_FLAG);
	return (T_UNKNOWN);
}
