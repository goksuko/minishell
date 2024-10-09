#include "../../includes/minishell.h"

int	ft_echo(char **cmds, t_info *info)
{
	printf("---FT__ECHO----\n");
	int		i;
	bool	n_flag;

	i = 0;
	n_flag = false;
	if (cmds == NULL)
	{
		ft_putstr_fd("", info->fd_out);
		return (SUCCESS);
	}
	if (cmds[i] != NULL && ft_strlen(cmds[i]) == 2 && ft_strncmp(cmds[i], "-n", 2) == 0) // substr would be cmds[1] = "-n", else if there are several flags 
	{
		n_flag = true;
		while (cmds[i] != NULL && ft_strlen(cmds[i]) == 2 && ft_strncmp(cmds[i], "-n", 2) == 0 && cmds[i] != NULL)
			i++;
	}
	while (cmds[i] != NULL)
	{
		ft_putstr_fd(cmds[i], info->fd_out);
			if (cmds[i + 1] != NULL)
				ft_putchar_fd(' ', info->fd_out);
		i++;
	}
	if (n_flag == false)
		ft_putchar_fd('\n', info->fd_out);
	return (SUCCESS);
}