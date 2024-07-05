/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readline.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: akaya-oz <akaya-oz@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/05 22:57:20 by akaya-oz      #+#    #+#                 */
/*   Updated: 2024/07/05 22:58:54 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*g_line_read = (char *) NULL;

char	*rl_gets(void)
{
	if (g_line_read)
	{
		free(g_line_read);
		g_line_read = (char *) NULL;
	}
	g_line_read = readline("prompt> ");
	if (g_line_read && *g_line_read)
	{
		add_history(g_line_read);
	}
	return (g_line_read);
}

int	main(void)
{
	char	*line;

	while ((line = rl_gets()))
	{
		printf("Got: %s\n", line);
	}
	return (0);
}
