/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/21 14:31:30 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/25 13:28:00 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_parent_sigint(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_redisplay();
	}
}

void	handle_child_sigint(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_replace_line("", 0);
	}
}

void	handle_child_sigquit(int signal)
{
	if (signal == SIGQUIT)
		write(STDERR_FILENO, "Quit\n", 5);
}

void	handle_signals(int process)
{
	if (process == PARENT)
	{
		signal(SIGINT, handle_parent_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (process == CHILD)
	{
		signal(SIGINT, handle_child_sigint);
		signal(SIGQUIT, handle_child_sigquit);
	}
	else if (process == HEREDOC)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
}