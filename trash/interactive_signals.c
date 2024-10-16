/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/03 13:48:44 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/09/03 13:48:44 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Ctrl + c = SIGINT -> Set up a signal handler for SIGINT to handle interruptions and display a new prompt.
Ctrl + \ = SIGQUIT -> Set up a signal handler for SIGQUIT to handle quitting the shell.
Ctrl + D = EOF -> Detect EOF in your input reading logic to exit the shell.

*/

/*
tcgetattr() gets the parameters associated with the terminal referred to by fd and stores them in the termios structure referenced by termios_p.

struct termios {
	tcflag_t c_iflag;       // input modes: Control how input is handled (e.g., line buffering, special characters).
	tcflag_t c_oflag;       // output modes:  Control how output is handled (e.g., automatic newline conversion).
	tcflag_t c_cflag;       // control modes:  Set data transmission parameters (e.g., baud rate, character size).
	tcflag_t c_lflag;       // local modes: Control various features like echoing and canonical mode (line-by-line vs. character-by-character input).
	cc_t c_line;            // line discipline: 
	cc_t c_cc[NCCS];        // control characters: Define special control characters like Ctrl+C or Ctrl+Z.
};
*/

/*
ECHOCTL flag, which controls whether control characters are echoed 
back to the terminal as ^X notation. This means that after calling 
this function, control characters you type into the terminal will 
not be displayed in ^X notation.
*/

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
		termios.c_lflag &=  ~ECHOCTL;
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
	// rl_replace_line("", 0); only commented out as not working on MAC
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