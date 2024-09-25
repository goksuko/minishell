#include "../../includes/minishell.h"

int	ft_echo(char *str, t_pipex *info)
{
	printf("---FT__ECHO----\n");
	printf("In echo string to print: %s\n", str);
	int		i;
	bool	n_flag;

	i = 0;
	n_flag = false;
	if (str[i] == '\0')
		ft_putstr_fd("", info->fd_out);
	while (str[i] != '\0' && str[i] == ' ')
		i++;
    while (str[i] != '\0' && ft_strncmp(&str[i], "-n", 2) == 0 \
		&& (str[i + 2] == ' ' || str[i + 2] == '\0'))
	{
		n_flag = true;
		i += 2;
		while (str[i] == ' ' && str[i] != '\0')
			i++;
	}
	ft_putstr_fd(&str[i], info->fd_out);
	if (n_flag == false)
		ft_putchar_fd('\n', info->fd_out); // changed from STDERR_FILENO to info->fd_out
	return (SUCCESS);
}