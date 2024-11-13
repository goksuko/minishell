/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 13:45:50 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/11/09 22:37:54 by akaya-oz      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_output_fd(t_info *info)
{
	if (info->fd_out == -10)
		return (STDOUT_FILENO);
	else
		return (info->fd_out);
}

bool	check_n_flag(char **cmds, int *index)
{
	bool	n_flag;
	int		i;

	n_flag = false;
	i = 0;
	if (cmds[i] != NULL && ft_strlen(cmds[i]) == 2 && \
	ft_strncmp(cmds[i], "-n", 2) == 0)
	{
		n_flag = true;
		while (cmds[i] != NULL && ft_strlen(cmds[i]) == 2 && \
		ft_strncmp(cmds[i], "-n", 2) == 0)
			i++;
	}
	*index = i;
	return (n_flag);
}

void	print_commands(char **cmds, int start_index, int out_fd)
{
	int	i;

	i = start_index;
	// printf("----PRINT COMMANDS----\n"); // DEBUGGING PURPOSES!
	// printf_array(cmds); // DEBUGGING PURPOSES!
	while (cmds[i] != NULL)
	{
		ft_putstr_fd(cmds[i], out_fd);
		if (cmds[i + 1] != NULL)
			ft_putchar_fd(' ', out_fd);
		i++;
	}
}

int	print_home_env_value(t_env *env, char *env_key, t_data *data)
{
	int	key_len;

	key_len = ft_strlen(env_key);	
	while (env != NULL && env->value != NULL)
	{
		if (ft_strncmp(env->key, env_key, key_len) == 0 && (int)ft_strlen(env->key) == key_len)
			printf("%s\n", env->value);
		env = env->next;
	}
	if (env == NULL || errno == ENOMEM)
	{
		free_system_error(data, ERROR_HOME_DIR);
		return (ERROR_HOME_DIR);
	}
	return (SUCCESS);
}

int	ft_echo(char **cmds, t_info *info)
{
	// printf("----ECHO----\n");
	int		i;
	bool	n_flag;
	int		out_fd;
	int		return_value;

	return_value = SUCCESS;
	out_fd = get_output_fd(info);
	if (cmds == NULL)
	{
		ft_putstr_fd("", out_fd);
		return (return_value);
	}
	n_flag = check_n_flag(cmds, &i);
	if (ft_strncmp(cmds[i], "~", 1) && ft_strlen(cmds[i]) == 1) // NEW. TO BE FIXED
	{
		return_value = print_home_env_value(info->data->env_list, "HOME", info->data);
		if (return_value != SUCCESS)
			return (return_value);
		i++;
	}
	print_commands(cmds, i, out_fd);
	if (n_flag == false)
		ft_putchar_fd('\n', out_fd);
	// printf("----ECHO DONE----\n");
	return (return_value);
}


// echo ~ needs to print HOME var. 
// BUT Check first if HOME exists at all in the env var
//  or if it has been unset
