#include "../../includes/minishell.h"

int	ft_pwd(char *str, t_data *shell_data)
{
	char	*cwd;
	int		i;

	cwd = NULL;
	i = 0;
	if (str[i] != '\0')
		ft_exit_data_perror(shell_data, ERROR_TOO_MAY_ARGS, "pwd: too many arguments");
	cwd = getcwd(cwd, 0);
	if (cwd == NULL)
		return (1); // should exit here or simply return 1 to indicate error??
	ft_putendl_fd(cwd, shell_data->info->fd_out);
	free(cwd);
	return (SUCCESS);
}
