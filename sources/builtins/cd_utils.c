/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/04 14:21:08 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/11/04 14:21:08 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_env_list(t_env **env_list, char *old_cwd, char *new_cwd)
{
	t_env	*env;

	env = *env_list;
	while (env != NULL)
	{
		if (ft_strncmp("OLDPWD", env->key, 6) == 0)
		{
			free(env->value); // Need to leave this in! Otherwise, it will cause a memory leak
			env->value = old_cwd;
		}
		else if (ft_strncmp("PWD", env->key, 3) == 0)
		{
			free(env->value); // Need to leave this in! Otherwise, it will cause a memory leak
			env->value = new_cwd;
		}
		env = env->next;
	}
}

int	cd_parent_dir(char *cwd, t_data *data)
{
	if (ft_strlen(cwd) != 1)
	{
		if (errno == ENOMEM || chdir("..") != 0)
		{
			free(cwd);
			free_system_error(data, ERROR_PARENT_DIR);
			return (ERROR_PARENT_DIR);
		}
		cwd = getcwd(NULL, 0);
		if (errno == ENOMEM || cwd == NULL)
		{
			free_system_perror(data, ERROR_ALLOCATION, "cwd in cd_parent_dir");
			return (ERROR_ALLOCATION);
		}
	}
	return (SUCCESS);
}


// if HOME does not exist we need to free cwd and old cwd in cd_data!! 
int	cd_home(t_env *env_list, t_data *data, t_cd_data *cd_data)
{
	char	*home;

	home = ft_get_env(env_list, "HOME");
	if (errno == ENOMEM || home == NULL)
	{
		free(cd_data->cwd); // NEW
		free_system_error(data, ERROR_HOME_DIR);
		return (ERROR_HOME_DIR);
	}
	if (errno == ENOMEM || chdir(home) != 0)
	{
		free(cd_data->cwd); // NEW
		free_system_error(data, ERROR_NO_FILE_DIR);
		return (ERROR_NO_FILE_DIR);
	}
	return (SUCCESS);
}

int	cd_old_pwd(t_env *env_list, t_data *data)
{
	char	*old_pwd;

	old_pwd = ft_get_env(env_list, "OLDPWD");
	if (errno == ENOMEM || old_pwd == NULL)
	{
		free_system_error(data, ERROR_OLDPWD);
		return (ERROR_OLDPWD);
	}
	if (errno == ENOMEM || chdir(old_pwd) != 0)
	{
		free(old_pwd);
		free_system_error(data, ERROR_NO_FILE_DIR);
		return (ERROR_NO_FILE_DIR);
	}
	return (SUCCESS);
}
