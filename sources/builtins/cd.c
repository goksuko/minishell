/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 13:45:47 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/11/18 11:06:41 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	ft_cd_error(t_data *data, char **cwd, char **old_cwd, int return_value)
int	ft_cd_error(t_data *data, char **cwd, int return_value)
{
	// printf("----FT_CD_ERROR----\n");
	// free_and_null(&*old_cwd); // Debugging purposes 
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

int	handle_cd_error(t_cd_data *cd_data, int error_code)
{
	// printf("----HANLDE_CD_ERROR----\n");
	return (ft_cd_error(cd_data->data, &cd_data->cwd, \
	error_code));
}

int	change_directory(char *path, t_cd_data *cd_data)
{
	printf("----CHANGE DIRECTORY-----\n");
	if (errno == ENOMEM || chdir(path) != 0)
		return (handle_cd_error(cd_data, ERROR_NO_FILE_DIR));
	return (SUCCESS);
}

int	handle_special_cases(char **cmds, t_cd_data *cd_data)
{
	// printf("---HANDLE SPECIAL CASES---\n");
	int	cmd_len;

	cmd_len = ft_strlen(cmds[0]);
	if (cmds[0] == NULL || (ft_strncmp(cmds[0], "~", 1) == 0 && cmd_len == 1))
		return (cd_home(cd_data->env_list, cd_data->data, cd_data));
	else if (ft_strncmp(cmds[0], "-", 1) == 0 && cmd_len == 1)
		return (cd_old_pwd(cd_data->env_list, cd_data->data, cd_data));
	else if (ft_strncmp(cmds[0], "..", 2) == 0 && cmd_len == 2)
		return (cd_parent_dir(cd_data->cwd, cd_data->data, cd_data));
	else if (ft_strncmp(cmds[0], "/", 1) == 0 && cmd_len == 1)
		return (change_directory("/", cd_data));
	else if (access(cmds[0], F_OK) == 0)
		return (change_directory(cmds[0], cd_data));
	return (handle_cd_error(cd_data, ERROR_NO_FILE_DIR));
}

int	ft_cd(char **cmds, t_env *env_list, t_data *data)
{
	t_cd_data	cd_data;
	int			return_value;

	cd_data.data = data;
	cd_data.env_list = env_list;
	cd_data.cwd = getcwd(NULL, 0);
	if (errno == ENOMEM || cd_data.cwd == NULL)
		return (handle_cd_error(&cd_data, ERROR_ALLOCATION));
	cd_data.old_cwd = cd_data.cwd;
	if (cmds && cmds[0] != NULL && cmds[1] != NULL)
		return (handle_cd_error(&cd_data, ERROR_TOO_MANY_ARGS));
	return_value = handle_special_cases(cmds, &cd_data);
	if (return_value != SUCCESS)
		return (return_value);
	cd_data.cwd = getcwd(NULL, 0);
	if (errno == ENOMEM || cd_data.cwd == NULL)
		return (handle_cd_error(&cd_data, ERROR_ALLOCATION));
	update_env_list(&env_list, cd_data.old_cwd, cd_data.cwd, &cd_data);
	return (return_value);
}
