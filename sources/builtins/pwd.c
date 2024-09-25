#include "../../includes/minishell.h"

int	ft_pwd(char *str, t_data *shell_data)
{
	char	*cwd;
	int		i;

	i = 0;
	if (str[i] != '\0')
	
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