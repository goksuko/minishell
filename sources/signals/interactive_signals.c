/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   interactive_signals.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/21 14:59:49 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/21 14:59:49 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	not_output_signal_keys()
{
	struct termios	termios;

	if (isatty(STDIN_FILENO))
	{
		if (tcgetattr(STDIN_FILENO, &termios) == -1)
		{
			printf("Error: not print signal keys: tcgetattr failed: %s\n", strerror(errno));
			return ;
		}
		termios.c_lflag &=  ~ECHO;
		if (tcsetattr(STDIN_FILENO, TCSANOW, &termios) == -1)
		{
			printf("Error: not print signal keys: tcsetattr failed: %s\n", strerror(errno));
			return ;
		}
	}
}

void	handle_sigint_interactive(int signal)
{
	(void)signal;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_siquit_interactive(int signal)
{
	(void)signal;
	rl_redisplay();
	ft_putstr_fd("Quit (core dumped)\n", 1);
}

void	interactive_signals(void)
{
	not_output_signal_keys();
	signal(SIGINT, handle_sigint_interactive);
	signal(SIGQUIT, handle_siquit_interactive);
}