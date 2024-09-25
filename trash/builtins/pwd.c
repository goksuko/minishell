#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (cwd == NULL)
		return (1); // should exit here or simply return 1 to indicate error??
	ft_putstr_fd(cwd, 1);
	ft_putchar_fd('\n', 1);
	free(cwd);
	return (SUCCESS);
}

//fd_out