#include "../../includes/minishell.h"

void	update_env_list(t_env **env_list, char *cwd, char *old_vs_cur_pwd) // may be moved to env_list_utils.c
{

}

int	cd_parent_dir(t_env *list)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (cwd == NULL)
		return (ERROR_ALLOCATION);
	if (ft_strncmp(cwd, "/", 1) != 0)
	{
		if (chdir("..") != 0)
		{
			free(cwd);
			return (ERROR_PARENT_DIR);
		}
	}
	free(cwd);
	return (SUCCESS);
}

int	cd_home(t_env *env_list)
{
	char *home;

	home = ft_get_env(env_list, "HOME");
	if (home == NULL)
		return(ERROR_HOME_DIR);
	if (chdir(home) != 0)
		return(ERROR_NO_FILE_DIR);
	return (SUCCESS);
}

int	cd_old_pwd(t_env *env_list)
{
	char	*old_pwd;

	old_pwd = ft_get_env(env_list, "OLD_PWD");
	if (old_pwd == NULL)
		return (ERROR_OLDPWD);
	if (chdir(old_pwd) != 0)
		return(ERROR_NO_FILE_DIR);
	return (SUCCESS);
}

int	ft_cd(char **cmds, t_data *shell_data, t_env *env_list)
{
	char	*cwd;
	int		return_value;

	cwd = NULL;
	return_value = -1;
	if (cmds != NULL && cmds[1] != NULL)
		return(ERROR_TOO_MANY_ARGS);
	cwd = getcwd(cwd, 0);
	if (cwd == NULL)
		return (ERROR_ALLOCATION);
	if (cmds[0] == NULL || ft_strncmp(cmds[0], '~', 1) == 0)
		return_value = cd_home(env_list);
	else if (cmds[0] == '-')
		return_value = cd_old_pwd(env_list);
	else if (ft_strncmp(cmds[0], "..", 2) == 0 && ft_strlen(cmds[0]) == 2)
		return_value = cd_parent_dir(env_list);
	else if (access(cmds[0], F_OK) == 0)
	{
		if (chdir(cmds[0]) != 0)
			return_value = ERROR_NO_FILE_DIR;
	}
	else if (cmds[0] != NULL)
		return_value = ERROR_NO_FILE_DIR;
	update_env_list(&env_list, cwd, "OLDPWD"); // or call update_shell() and update_path()
	free(cwd);
	cwd = getcwd(cwd, NULL);
	update_env_list(&env_list, cwd, "PWD");
	free(cwd);
	return (SUCCESS);
}