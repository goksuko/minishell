/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollar_sign_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/24 15:50:59 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/24 15:50:59 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_str(t_data *data, char *str, int *index)
{
	char	*env;
	char	*temp;
	int		i;

	i = 0;
	env = NULL;
	while (str[i] != '\0' && (ft_isalnum(str[i]) == 1 || str[i] == '_'))
		i++;
	temp = (char *)ft_calloc(sizeof(char), i + 1);
	if (temp == NULL)
		return (NULL);
	ft_strlcpy(temp, str, i + 1);
	env = ft_get_env(data->env_list, temp);
	free (temp);
	if (env == NULL)
	{
		env = ft_strdup("");
		if (env == NULL)
			return (NULL);
	}
	(*index) += i;
	return (env);
}

char	*expand_exit_code(t_data *data, int *i)
{
	char	*temp;

	temp = NULL;
	temp = ft_itoa(data->exit_code);
	if (temp == NULL)
		return (NULL);
	(*i)++;
	return (temp);
}

char	*expand_pid(int *i)
{
	char	*temp;

	temp = NULL;
	temp = ft_itoa(getpid());
	if (temp == NULL)
		return (NULL);
	(*i)++;
	return (temp);
}

char	*expand_env_variable(t_data *data, char *str, int *i)
{
	return (get_env_str(data, str, i));
}

char	*process_dollar_sign(t_data *data, char *str, int *i)
{
	if (str[0] == '?')
		return (expand_exit_code(data, i));
	else if (str[0] == '$')
		return (expand_pid(i));
	else if (str[0] != '\0' && (ft_isalnum(str[0]) == 1 ||\
	str[0] == '_')) // "_" or " " ??
		return (expand_env_variable(data, str, i));
	return (NULL);
}