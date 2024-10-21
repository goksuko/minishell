/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/22 15:13:12 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/19 13:04:57 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// TO BE FIXED. NO GLOBAL VARIABLES ALLOWED

static char	*line_read = (char *)NULL;

char	*rl_gets(void)
{
	if (line_read)
	{
		free(line_read);
		line_read = (char *)NULL;
	}
	line_read = readline(">[minishell]: ");
	if (line_read == NULL)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(0);
	}
	if (line_is_empty(line_read) == true)
	{
		line_read = ft_strdup(" ");
		return (line_read);
	}
	if (line_is_whitespace(line_read) == true)
	{
		add_history(line_read);
		free(line_read);
		line_read = ft_strdup(" ");
		return (line_read);
	}
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}
