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

// void	output_ctrl()
// {
// 	struct termios	term;

// 	if (isatty(STDIN_FILENO) == 1)
// 	{
// 		// error handling;
// 		printf("Error: isatty failed\n");
// 	}
// 	if (tcgetattr(STDIN_FILENO, term) == -1)
// 	{
// 		// error handling;
// 		printf("Error: tcgetattr failed\n");
// 	}
// 	term->cl


// }

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
	ft_putstr_fd("Quit (core dumped)\n", 1);
}

void	signal_handling(void)
{
	// output_ctrl();
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_siquit);
}