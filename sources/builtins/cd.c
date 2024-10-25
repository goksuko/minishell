/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 13:45:47 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/25 13:45:47 by vbusekru      ########   odam.nl         */
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

int	cd_home(t_env *env_list, t_data *data)
{
	char	*home;

	home = ft_get_env(env_list, "HOME");
	if (errno == ENOMEM || home == NULL)
	{
		free_system_error(data, ERROR_HOME_DIR);
		return (ERROR_HOME_DIR);
	}
	if (errno == ENOMEM || chdir(home) != 0)
	{
		free(home);
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

// int	ft_cd(char **cmds, t_env *env_list, t_data *data)
// {
// 	char	*cwd;
// 	char	*old_cwd;
// 	int		return_value;
// 	int		cmd_len;

// 	return_value = -1;
// 	if (errno == ENOMEM || (cmds && cmds[0] != NULL && cmds[1] != NULL))
// 	{
// 		free_system_error(data, ERROR_TOO_MANY_ARGS);
// 		return (ERROR_TOO_MANY_ARGS);
// 	}
// 	cmd_len = ft_strlen(cmds[0]);
// 	cwd = getcwd(NULL, 0);
// 	if (errno == ENOMEM || cwd == NULL)
// 	{
// 		free_system_perror(data, ERROR_ALLOCATION, "cwd in cd");
// 		return (ERROR_ALLOCATION);
// 	}
// 	old_cwd = ft_strdup(cwd);
// 	if (errno == ENOMEM || old_cwd == NULL)
// 	{
// 		free_system_perror(data, ERROR_ALLOCATION, "old_cwd in cd");
// 		free(cwd);  // to be checked again
// 		return (ERROR_ALLOCATION);
// 	}
// 	if (cmds[0] == NULL || (ft_strncmp(cmds[0], "~", 1) == 0 && cmd_len == 1))
// 		return_value = cd_home(env_list, data);
// 	else if (ft_strncmp(cmds[0], "/", 1) == 0 && cmd_len == 1)
// 	{
// 		if (errno == ENOMEM || chdir("/") != 0)
// 		{
// 			free_system_error(data, ERROR_NO_FILE_DIR);
// 			free(old_cwd);  // to be checked again
// 			free(cwd);  // to be checked again
// 			return_value = ERROR_NO_FILE_DIR;
// 		}
// 	}
// 	else if (ft_strncmp(cmds[0], "-", 1) == 0 && cmd_len == 1)
// 	{
// 		return_value = cd_old_pwd(env_list, data);
// 		if (return_value != SUCCESS)
// 		{
// 			free(old_cwd);  // to be checked again
// 			free(cwd);  // to be checked again
// 			return (return_value);
// 		}
// 	}
// 	else if (ft_strncmp(cmds[0], "..", 2) == 0 && cmd_len == 2)
// 	{
// 		return_value = cd_parent_dir(cwd, data);
// 		if (return_value != SUCCESS)
// 		{
// 			free(old_cwd);  // to be checked again
// 			free(cwd);  // to be checked again
// 			return (return_value);
// 		}
// 	}
// 	else if (access(cmds[0], F_OK) == 0)
// 	{
// 		if (errno == ENOMEM || chdir(cmds[0]) != 0)
// 		{
// 			free(old_cwd);  // to be checked again
// 			free(cwd);  // to be checked again
// 			free_system_error(data, ERROR_NO_FILE_DIR);
// 			return_value = ERROR_NO_FILE_DIR;
// 		}
// 	}
// 	else if (errno == ENOMEM || cmds[0] != NULL)
// 	{
// 		free(old_cwd);  // to be checked again
// 		free(cwd); // to be checked again
// 		free_system_error(data, ERROR_NO_FILE_DIR);
// 		return_value = ERROR_NO_FILE_DIR;
// 	}
// 	cwd = getcwd(NULL, 0);
// 	if (errno == ENOMEM || cwd == NULL)
// 	{
//         free(old_cwd);
//         free_system_perror(data, ERROR_ALLOCATION, "cwd in cd");
//         return (ERROR_ALLOCATION);
//     }
// 	update_env_list(&env_list, old_cwd, cwd);
// 	return (return_value);
// }

int ft_cd_error(t_data *data, char **cwd, char **old_cwd, int return_value)
{
	free_and_null(&*old_cwd);
	free_and_null(&*cwd);
	if (return_value == ERROR_TOO_MANY_ARGS)
	{
		free_system_error(data, ERROR_TOO_MANY_ARGS);
		return (ERROR_TOO_MANY_ARGS);
	}
	else if (return_value == ERROR_ALLOCATION)
	{
		free_system_perror(data, ERROR_ALLOCATION, "ft_cd");
		return (ERROR_ALLOCATION);
	}
	else if (return_value == ERROR_NO_FILE_DIR)
	{
		free_system_error(data, ERROR_NO_FILE_DIR);
		return (ERROR_NO_FILE_DIR);
	}
	return (SUCCESS);
}

int	ft_cd(char **cmds, t_env *env_list, t_data *data)
{
	char	*cwd;
	char	*old_cwd;
	int		return_value;
	int		cmd_len;

	return_value = -1;
	cwd = NULL;
	old_cwd = NULL;
	if (errno == ENOMEM || (cmds && cmds[0] != NULL && cmds[1] != NULL))
		return(ft_cd_error(data, &cwd, &old_cwd, ERROR_TOO_MANY_ARGS));
	cmd_len = ft_strlen(cmds[0]);
	cwd = getcwd(NULL, 0);
	if (errno == ENOMEM || cwd == NULL)
		return(ft_cd_error(data, &cwd, &old_cwd, ERROR_ALLOCATION));
	old_cwd = ft_strdup(cwd);
	if (errno == ENOMEM || old_cwd == NULL)
		return(ft_cd_error(data, &cwd, &old_cwd, ERROR_ALLOCATION));
	if (cmds[0] == NULL || (ft_strncmp(cmds[0], "~", 1) == 0 && cmd_len == 1))
		return_value = cd_home(env_list, data);
	else if (ft_strncmp(cmds[0], "/", 1) == 0 && cmd_len == 1)
	{
		if (errno == ENOMEM || chdir("/") != 0)
			return(ft_cd_error(data, &cwd, &old_cwd, ERROR_NO_FILE_DIR));
	}
	else if (ft_strncmp(cmds[0], "-", 1) == 0 && cmd_len == 1)
	{
		return_value = cd_old_pwd(env_list, data);
		if (return_value != SUCCESS)
			ft_cd_error(data, &cwd, &old_cwd, return_value);
	}
	else if (ft_strncmp(cmds[0], "..", 2) == 0 && cmd_len == 2)
	{
		return_value = cd_parent_dir(cwd, data);
		if (return_value != SUCCESS)
			ft_cd_error(data, &cwd, &old_cwd, return_value);
	}
	else if (access(cmds[0], F_OK) == 0)
	{
		if (errno == ENOMEM || chdir(cmds[0]) != 0)
			return(ft_cd_error(data, &cwd, &old_cwd, ERROR_NO_FILE_DIR));
	}
	else if (errno == ENOMEM || cmds[0] != NULL)
		return(ft_cd_error(data, &cwd, &old_cwd, ERROR_NO_FILE_DIR));
	cwd = getcwd(NULL, 0);
	if (errno == ENOMEM || cwd == NULL)
		return(ft_cd_error(data, &cwd, &old_cwd, ERROR_ALLOCATION));
	update_env_list(&env_list, old_cwd, cwd);
	return (return_value);
}