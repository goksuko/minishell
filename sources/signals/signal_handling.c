/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handling.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 13:48:44 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/09/03 13:48:44 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Ctrl + c = SIGINT
Ctrl + \ = SIGQUIT
Ctrl + D = EOF
*/

void	handle_sigint(int signal)
{
	(void)signal;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_siquit(int signal)
{
	(void)signal;
	rl_redisplay();
	// Error message needed to be printed here ?
}

void	signal_handling(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_siquit);
}