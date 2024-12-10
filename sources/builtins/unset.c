/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vbusekru <vbusekru@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/25 13:46:40 by vbusekru      #+#    #+#                 */
/*   Updated: 2024/10/25 13:46:40 by vbusekru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset_env_var(char *key, t_env **env_list)
{
	t_env	*temp;
	t_env	*prev;
	int		key_len;

	temp = *env_list;
	prev = NULL;
	key_len = ft_strlen(key);
	while (temp != NULL)
	{
		if ((int)ft_strlen(temp->key) == key_len && ft_strcmp(temp->key, key) == 0)
		// if ((int)ft_strlen(temp->key) == key_len && ft_strncmp(temp->key, key,
		// 		key_len) == 0)
		{
			if (prev == NULL)
				*env_list = temp->next;
			else
				prev->next = temp->next;
			free(temp->key);
			free(temp->value);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}

int	ft_unset(char **cmds, t_data *data)
{
	int	i;

	i = 0;
	if (cmds[0] == NULL)
		return (SUCCESS);
	while (cmds[i] != NULL)
	{
		unset_env_var(cmds[i], &data->env_list);
		i++;
	}
	return (SUCCESS);
}
