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

bool	check_n_flag(char **cmds, int *index, bool *n_flag)
{
	int		i;
	int		j;

	i = 0;
	while (cmds[i] != NULL)
	{
		if (cmds[i][0] == '-' && cmds[i][1] == 'n')
		{
			j = 1;
			while (cmds[i][j] == 'n')
				j++;
			if (cmds[i][j] == '\0')
			{
				*n_flag = true;
				i++;
			}
			else
				break ;
		}
		else
			break ;
	}
	*index = i;
	return (*n_flag);
}

int	print_home_env_value(t_env *env, t_data *data)
{
	char	*env_value;

	env_value = NULL;
	while (env != NULL && env->value != NULL)
	{
		if (ft_strncmp(env->key, "HOME", 4) == 0 && \
			(int)ft_strlen(env->key) == 4)
			env_value = env->value;
		env = env->next;
	}
	if (env_value == NULL || errno == ENOMEM)
	{
		free_system_error(data, ERROR_HOME_DIR);
		return (ERROR_HOME_DIR);
	}
	else
		ft_putstr_fd(env_value, STDOUT_FILENO);
	return (SUCCESS);
}

int	print_commands(char **cmds, int start_index, int out_fd, t_info *info)
{
	int	i;
	int	return_value;

	i = start_index;
	return_value = SUCCESS;
	while (cmds[i] != NULL)
	{
		if (ft_strncmp(cmds[i], "~", 1) == 0 && ft_strlen(cmds[i]) == 1)
		{
			return_value = print_home_env_value(info->data->env_list, \
				info->data);
			if (return_value != SUCCESS)
				return (return_value);
		}
		else
		{
			ft_putstr_fd(cmds[i], out_fd);
			if (cmds[i + 1] != NULL)
				ft_putchar_fd(' ', out_fd);
		}
		i++;
	}
	return (return_value);
}

int	ft_echo(char **cmds, t_info *info)
{
	int		i;
	bool	n_flag;
	int		out_fd;
	int		return_value;

	i = 0;
	n_flag = false;
	return_value = SUCCESS;
	out_fd = get_output_fd(info);
	if (cmds == NULL)
	{
		ft_putstr_fd("", out_fd);
		return (return_value);
	}
	check_n_flag(cmds, &i, &n_flag);
	print_commands(cmds, i, out_fd, info);
	if (n_flag == false)
		ft_putchar_fd('\n', out_fd);
	return (return_value);
}
