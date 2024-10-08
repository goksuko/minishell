/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/22 15:13:12 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/02 10:12:04 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*line_read = (char *) NULL;

char	*rl_gets(void)
{
	if (line_read)
	{
		free(line_read);
		line_read = (char *) NULL;
	}
	// line_read = readline("\033[36mminishell of \U0001F9B8 \033[35mGoksu\033[36m & \U0001F9DA \033[33mVanessa\033[36m > \033[0m");
	line_read = readline("> ");
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}
