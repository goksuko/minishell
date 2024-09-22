/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_types.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 14:32:37 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/09/14 21:18:00 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*token_type_to_string(t_token_type type) // to be deleted later
{
	static char	*str[] = {
	[T_BUILTIN] = "BUILTIN",
	[T_IDENTIFIER] = "IDENTIFIER",
	[T_SMALLER] = "SMALLER",
	[T_GREATER] = "GREATER",
	[T_DSMALLER] = "DSMALLER",
	[T_DGREATER] = "DGREATER",
	[T_PIPE] = "PIPE",
	[T_FLAG] = "FLAG",
	[T_SINGLE_QUOTES] = "SINGLE_QUOTES",
	[T_DOUBLE_QUOTES] = "DOUBLE_QUOTES",
	[T_UNKNOWN] = "UNKNOWN"};

	if (type < 0 || type >= sizeof(str) / sizeof(str[0])) // need to check this
		return (str[T_UNKNOWN]);
	return (str[type]);
}

t_token_type	check_command(char *token)
{
	if (ft_strncmp(token, "echo", 4) == 0)
		return (T_BUILTIN);
	if (ft_strncmp(token, "cd", 2) == 0)
		return (T_BUILTIN);
	if (ft_strncmp(token, "pwd", 3) == 0)
		return (T_BUILTIN);
	if (ft_strncmp(token, "export", 6) == 0)
		return (T_BUILTIN);
	if (ft_strncmp(token, "unset", 5) == 0)
		return (T_BUILTIN);
	if (ft_strncmp(token, "env", 3) == 0)
		return (T_BUILTIN);
	if (ft_strncmp(token, "exit", 4) == 0)
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
