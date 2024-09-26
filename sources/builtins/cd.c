#include "../../includes/minishell.h"

int	ft_cd(char *str, t_data *shell_data, t_env *env_list)
{
	char	*old_pwd;
	int		i;

	i = 0;
	if (str[i] == '\0' || str[i] == '~')
		home_dir(shell_data, env_list);
	else if (str[i] == '-')
		back_to_old_pwd(shell_data, env_list);
}