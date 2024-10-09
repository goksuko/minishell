#include "../../includes/minishell.h"

int	ft_pwd(char **cmds, t_data *data)
{
	char	*cwd;

	cwd = NULL;
	if (cmds[0] != NULL)
		return(ERROR_TOO_MANY_ARGS);
	cwd = getcwd(cwd, 0);
	if (cwd == NULL)
		return (ERROR_ALLOCATION);
	ft_putendl_fd(cwd, data->info->fd_out);
	free(cwd);
	return (SUCCESS);
}
