#include "../../includes/minishell.h"

int	ft_echo(char **arguments)
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
		ft_putstr_fd(arguments[i], 1);
		if (arguments[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (n_flag == false)
		ft_putchar_fd('\n', 1);
	return (SUCCESS);
}