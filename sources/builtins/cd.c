#include "../../includes/minishell.h"

void	update_env_list(t_env **env_list, char *old_cwd, char *new_cwd)
{
	t_env	*env;

	env = *env_list;
	while (env != NULL)
	{
		if (ft_strncmp("OLDPWD", env->key, 6) == 0)
		{
			free(env->value);
			env->value = old_cwd;
		}
		else if (ft_strncmp("PWD", env->key, 3) == 0)
		{
			free(env->value);
			env->value = new_cwd;
		}
		env = env->next;
	}
}

int	cd_parent_dir(char *cwd)
{
	if (ft_strlen(cwd) != 1)
	{
		if (chdir("..") != 0)
		{
			free(cwd);
			return (ERROR_PARENT_DIR);
		}
		cwd = getcwd(NULL, 0);
	}
	return (SUCCESS);
}

int	cd_home(t_env *env_list)
{
	char	*home;

	home = ft_get_env(env_list, "HOME");
	if (home == NULL)
		return (ERROR_HOME_DIR);
	if (chdir(home) != 0)
		return (ERROR_NO_FILE_DIR);
	return (SUCCESS);
}

int	cd_old_pwd(t_env *env_list)
{
	char	*old_pwd;

	old_pwd = ft_get_env(env_list, "OLDPWD");
	if (old_pwd == NULL)
		return (ERROR_OLDPWD);
	if (chdir(old_pwd) != 0)
		return (ERROR_NO_FILE_DIR);
	return (SUCCESS);
}

int	ft_cd(char **cmds, t_env *env_list)
{
	char	*cwd;
	char	*old_cwd;
	int		return_value;
	int		cmd_len;

	return_value = -1;
	if (cmds[0] != NULL && cmds[1] != NULL)
		return (ERROR_TOO_MANY_ARGS);
	cmd_len = ft_strlen(cmds[0]);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (ERROR_ALLOCATION);
	old_cwd = cwd;
	if (cmds[0] == NULL || (ft_strncmp(cmds[0], "~", 1) == 0 && cmd_len == 1))
		return_value = cd_home(env_list);
	else if (ft_strncmp(cmds[0], "/", 1) == 0 && cmd_len == 1)
	{
		if (chdir("/") != 0)
			return_value = ERROR_NO_FILE_DIR;
	}
	else if (ft_strncmp(cmds[0], "-", 1) == 0 && cmd_len == 1)
		return_value = cd_old_pwd(env_list);
	else if (ft_strncmp(cmds[0], "..", 2) == 0 && cmd_len == 2)
		return_value = cd_parent_dir(cwd);
	else if (access(cmds[0], F_OK) == 0)
	{
		if (chdir(cmds[0]) != 0)
			return_value = ERROR_NO_FILE_DIR;
	}
	else if (cmds[0] != NULL)
		return_value = ERROR_NO_FILE_DIR;
	cwd = getcwd(NULL, 0);
	update_env_list(&env_list, old_cwd, cwd);
	return (return_value);
}
