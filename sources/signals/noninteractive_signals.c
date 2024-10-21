/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   noninteractive_signals.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/21 15:00:03 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/21 15:00:03 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	output_signal_keys()
{
	struct termios	termios;

	if (isatty(STDIN_FILENO))
	{
		if (tcgetattr(STDIN_FILENO, &termios) == -1)
		{
			printf("Error: print signal keys: tcgetattr failed: %s\n", strerror(errno));
			return ;
		}
		termios.c_lflag |=  ECHO;
		if (tcsetattr(STDIN_FILENO, TCSANOW, &termios) == -1)
		{
			printf("Error: print signal keys: tcsetattr failed: %s\n", strerror(errno));
			return ;
		}
	}
}

void	handle_sigint_noninteractive(int signal)
{
	(void)signal;
	ft_putchar_fd('\n', 1);
}

void	handle_siquit_noninteractive(int signal)
{
	(void)signal;
	ft_putstr_fd("Quit (core dumped)\n", 1);
}

void	noninteractive_signals(void)
{
	output_signal_keys();
	signal(SIGINT, handle_sigint_noninteractive);
	signal(SIGQUIT, handle_siquit_noninteractive);
}