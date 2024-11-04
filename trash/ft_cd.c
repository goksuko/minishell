
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
