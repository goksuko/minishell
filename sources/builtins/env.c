/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 13:45:56 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/25 13:45:56 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env(t_env *env)
{
	while (env != NULL && env->value != NULL)
	{
		printf("%s", env->key);
		printf("=");
		printf("%s\n", env->value);
		env = env->next;
	}
}

int	ft_env(char **cmds, t_data *data)
{
	t_env *env;
	int return_value;

	env = data->env_list;
	if (cmds[0] == NULL)
	{
		print_env(env);
		return_value = SUCCESS;
	}
	else
		return_value = ERROR_NO_FILE_DIR;
	return (return_value);
}