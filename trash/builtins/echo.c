#include "../../includes/minishell.h"

int	ft_echo(char **arguments, t_pipex *info)
{
	int		i;
	bool	n_flag;

	i = 1;
	n_flag = false;
	if (arguments[i] != NULL && ft_strncmp(arguments[i], "-n", 2) == 0)
	{
		n_flag = true;
		i++;
	}
	while (arguments[i] != NULL)
	{
		ft_putstr_fd(arguments[i], info->fd_out);
		if (arguments[i + 1])
			ft_putchar_fd(' ', info->fd_out);
		i++;
	}
	if (n_flag == false)
		ft_putchar_fd('\n', STDERR_FILENO);
	return (SUCCESS);
}