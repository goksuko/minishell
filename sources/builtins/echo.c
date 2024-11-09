/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 13:45:50 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/11/09 21:50:35 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_output_fd(t_info *info)
{
	if (info->fd_out == -10)
		return (STDOUT_FILENO);
	else
		return (info->fd_out);
}

bool	check_n_flag(char **cmds, int *index)
{
	bool	n_flag;
	int		i;

	n_flag = false;
	i = 0;
	if (cmds[i] != NULL && ft_strlen(cmds[i]) == 2 && \
	ft_strncmp(cmds[i], "-n", 2) == 0)
	{
		n_flag = true;
		while (cmds[i] != NULL && ft_strlen(cmds[i]) == 2 && \
		ft_strncmp(cmds[i], "-n", 2) == 0)
			i++;
	}
	*index = i;
	return (n_flag);
}

void	print_commands(char **cmds, int start_index, int out_fd)
{
	int	i;

	i = start_index;
	while (cmds[i] != NULL)
	{
		ft_putstr_fd(cmds[i], out_fd);
		if (cmds[i + 1] != NULL)
			ft_putchar_fd(' ', out_fd);
		i++;
	}
}

int	ft_echo(char **cmds, t_info *info)
{
	// printf("----ECHO----\n");
	int		i;
	bool	n_flag;
	int		out_fd;

	out_fd = get_output_fd(info);
	if (cmds == NULL)
	{
		ft_putstr_fd("", out_fd);
		return (SUCCESS);
	}
	n_flag = check_n_flag(cmds, &i);
	print_commands(cmds, i, out_fd);
	if (n_flag == false)
		ft_putchar_fd('\n', out_fd);
	// printf("----ECHO DONE----\n");
	return (SUCCESS);
}
