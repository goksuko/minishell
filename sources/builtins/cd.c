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

int	ft_cd_error(t_data *data, char **cwd, char **old_cwd, int return_value)
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

// int	handle_cd_error(t_data *data, char **cwd, char **old_cwd, int error_code)
// {
// 	return ft_cd_error(data, cwd, old_cwd, error_code);
// }

// int	change_directory(char *path, t_data *data, char **cwd, char **old_cwd)
// {
// 	if (errno == ENOMEM || chdir(path) != 0)
// 		return handle_cd_error(data, cwd, old_cwd, ERROR_NO_FILE_DIR);
// 	return SUCCESS;
// }

// int	handle_special_cases(char **cmds, t_env *env_list, t_data *data, char **cwd, char **old_cwd)
// {
// 	int cmd_len;

// 	cmd_len = ft_strlen(cmds[0]);
// 	if (cmds[0] == NULL || (ft_strncmp(cmds[0], "~", 1) == 0 && cmd_len == 1))
// 		return cd_home(env_list, data);
// 	else if (ft_strncmp(cmds[0], "-", 1) == 0 && cmd_len == 1)
// 		return cd_old_pwd(env_list, data);
// 	else if (ft_strncmp(cmds[0], "..", 2) == 0 && cmd_len == 2)
// 		return cd_parent_dir(*cwd, data);
// 	else if (ft_strncmp(cmds[0], "/", 1) == 0 && cmd_len == 1)
// 		return change_directory("/", data, cwd, old_cwd);
// 	else if (access(cmds[0], F_OK) == 0)
// 		return change_directory(cmds[0], data, cwd, old_cwd);
// 	return handle_cd_error(data, cwd, old_cwd, ERROR_NO_FILE_DIR);
// }

// int	ft_cd(char **cmds, t_env *env_list, t_data *data)
// {
// 	char	*cwd;
// 	char	*old_cwd;
// 	int		return_value;

// 	cwd = getcwd(NULL, 0);
// 	if (errno == ENOMEM || cwd == NULL)
// 		return handle_cd_error(data, &cwd, &old_cwd, ERROR_ALLOCATION);
// 	old_cwd = ft_strdup(cwd);
// 	if (errno == ENOMEM || old_cwd == NULL)
// 		return handle_cd_error(data, &cwd, &old_cwd, ERROR_ALLOCATION);
// 	if (cmds && cmds[0] != NULL && cmds[1] != NULL)
// 		return handle_cd_error(data, &cwd, &old_cwd, ERROR_TOO_MANY_ARGS);
// 	return_value = handle_special_cases(cmds, env_list, data, &cwd, &old_cwd);
// 	if (return_value != SUCCESS)
// 		return return_value;
// 	cwd = getcwd(NULL, 0);
// 	if (errno == ENOMEM || cwd == NULL)
// 		return handle_cd_error(data, &cwd, &old_cwd, ERROR_ALLOCATION);
// 	update_env_list(&env_list, old_cwd, cwd);
// 	return (return_value);
// }

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